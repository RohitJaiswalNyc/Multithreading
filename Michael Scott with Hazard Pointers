#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <array>
#include<deque>
#include<atomic>
#include<thread>
#include<future>
#include<memory>
// hashmap
// #include <ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
using namespace std;
 
#define rep(i,j,k) for(int i=j;i<=(int)k;i++)
#define forn(i,n) for(int i=0;i<(int)n;i++)
#define forn1(i,n) for(int i=1;i<=(int)n;i++)
#define per(i,j,k) for(int i=j;i>=k;i--)
#define en cout << "\n"
#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define pb push_back
#define eb emplace_back
#define f first
#define s second
#define sz(a) (int)a.size()
#define ins insert
typedef long long ll;
typedef long double ld;
#define pii pair<int,int>
#define pi pair<int,int>
#define pll pair<ll,ll>
#define plll pair<ll,pair<ll,ll>>
#define pli pair<ll,int>
#define vi vector<int>
#define vl vector<ll>
#define vvi vector<vi>
#define vvl vector<vl>
#define vll vector<pll>
#define vii vector<pii>
#define vvii vector<vii>
#define vlll vector<plll>
#define endl "\n"
#define ctz(n) __builtin_ctz(n)
#define clz(n) __builtin_clz(n)
#define parity(n) __builtin_parity(n)
#define popcnt(n) __builtin_popcount(n)
#define all(x) (x).begin(), (x).end()
#define unique(x) sort(all((x))); (x).resize(unique(all((x))) - (x).begin())
#define MEM(x) memset(x,0,sizeof(x))

// random number generater
std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
#define rndm(l,r) uniform_int_distribution<int>(l,r)(rng)
 
// get smaller/bigger value in a
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
 
// constants
ll oo = 2e18;
int inf = 1e9 + 5;
const int MOD = 998244353;
const int N = 2e5 + 5;

const int cores = thread::hardware_concurrency();
constexpr int RETIRE_THRESHOLD = 1e2;
int total_reps = 1e6;


template<typename T>
struct Node {
  atomic<Node*> next;
  T val;
  Node(): next(nullptr), val(T()){}
  Node(T _val): next(nullptr), val(_val){}
};



template <typename T>
class hazardManager{
  struct alignas(64) padded_hp {
    atomic<Node<T>*> ptr{nullptr};
  };

  struct alignas(64) padded_retired_list {
    vector<Node<T>*> list; // 24 bytes of real data
    // 40 bytes of invisible "padding" added by the compiler
  };
  
  vector<padded_hp> hazard_pointers;


public:
  vector<padded_retired_list> retired_list;

  hazardManager() : hazard_pointers(cores), retired_list(cores){}

  ~hazardManager(){
    forn(i,cores){
      for(Node<T>* node:retired_list[i].list){
        if(node) delete node;
      }
    }
  }

  void aquire(int tid,Node<T>* node){
    // assert(node != nullptr);
    if(node) hazard_pointers[tid].ptr.store(node, memory_order_seq_cst);
  }

  void release(int tid){
    hazard_pointers[tid].ptr.store(nullptr, memory_order_relaxed);
  }

  void retire(int tid, Node<T>* node){
    retired_list[tid].list.pb(node);
    if(sz(retired_list[tid].list) >= RETIRE_THRESHOLD){
      scan(tid);
    }
  }

  void scan(int tid){
    
    vector<Node<T>*> active_hps;
    for(const auto& x:hazard_pointers){
      Node<T>* p = x.ptr.load(memory_order_acquire);
      if(p) active_hps.pb(p);
    }
    sort(all(active_hps));
    vector<Node<T>*> remaining;

    for (Node<T>* node : retired_list[tid].list) {
        if (binary_search(all(active_hps), node)) {
            remaining.push_back(node);
        } else {
            delete node;
        }
    }
    retired_list[tid].list = move(remaining);
    
  }
  

};

template<typename T>
class LockFreeQueue{
private:  
  atomic<Node<T>*> head,tail;

  hazardManager<T>& hp;

public:
  atomic<bool> finished;  

  LockFreeQueue(hazardManager<T>& mgr): hp(mgr),finished{0}{
    Node<T>* dummy = new Node<T>{};
    head = dummy,tail = dummy;
  }

  void enqueue(T val){
    Node<T>* new_node = new Node(val);
    while(true){
      Node<T>* last = tail.load(memory_order_acquire);
      Node<T>* next = last->next.load(memory_order_acquire);
      if(last == tail.load(memory_order_acquire)){
        if(next == nullptr){
          if(last->next.compare_exchange_weak(next,new_node,memory_order_release,memory_order_relaxed)){
            tail.compare_exchange_weak(last,new_node,memory_order_release,memory_order_relaxed);
            return;
          }
        }
        else{
          // update tail
          tail.compare_exchange_weak(last,next,memory_order_release,memory_order_relaxed);
        }
      }
    }
  }

  // make this bool after checking enqueue
  void dequeue(T& result,int tid){
    while(true){
      Node<T>* h = head.load(memory_order_acquire);
      Node<T>* t = tail.load(memory_order_acquire);
      {
        // this code ensures that I have safely aquired next in my current hp thread
        hp.aquire(tid,h);
        std::atomic_thread_fence(memory_order_seq_cst);
  
        if(head.load(memory_order_acquire) != h){
          h = head.load(memory_order_acquire);
          hp.release(tid);
          continue;
        }
      }
      Node<T>* next = h->next.load(memory_order_acquire);
      if(h == head.load(memory_order_acquire)){
        if(h == t){
          // 1) if there is continuous data injection the in if loop 
          // we can make this thread sleep for some milli seconds
          // 2) We can have a while loop in solve where we check if 
          // everythread have become non joinable i.e. exited, and
          // if so return 0, else do this thread sleep and continue;
          // 3) To avoid empty queue when there are still more enqueue's left
          // is to have more producers than consumer.
          // 4) next up hazard pointers and then integrate hazard pointers
          // instead atomic<shared_ptr<>> 
          if(!next){
            if(finished){
              return;
            }
            else{
              // this_thread::sleep_for(chrono::microseconds(1000));
              continue;
            }
          }
          else{
            tail.compare_exchange_weak(t,next,memory_order_release,memory_order_relaxed);
          }
        }
        else{
          if(next){
            result = next->val;
            if(head.compare_exchange_weak(h,next,memory_order_release,memory_order_relaxed)){
              hp.release(tid);
              hp.retire(tid,h);
              return;
            }
          }
        }
      }
    }
  }

  void producer_thread(int left,int right){
    for(int i=left;i<=right;i++){
      enqueue(i);
    }
  }

  void consumer_thread(int left,int right,vi& res,int tid){
    this_thread::sleep_for(std::chrono::microseconds(2));
    for(int i=left;i<=right;i++){
      dequeue(res[i],tid);
    }
  }
};


void solve(){
  hazardManager<int> mgr;
  LockFreeQueue<int> lfq(mgr);
  vector<thread> prod,cons;
  
  vi res(cores*total_reps);
  forn(i,cores){
    prod.eb(&LockFreeQueue<int>::producer_thread,&lfq,i*total_reps,(i+1)*total_reps-1);
    cons.eb(&LockFreeQueue<int>::consumer_thread,&lfq,i*total_reps,(i+1)*total_reps-1,ref(res),i);
  }

  forn(i,cores){
    if(prod[i].joinable()) prod[i].join();
  }
  lfq.finished = 1;
  forn(i,cores){
    if(cons[i].joinable()) cons[i].join();
  }

  // for(auto &x:res){
  //   cout << x << " ";
  // }
  // en;
  // forn(i,cores){
  //   cout << mgr.retired_list[i].list.size() << " ";
  // }
  // en;
}

int main(){
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("1.txt","w",stdout);  
  #endif
  FAST;
  int _ = 1;
  cin >> _;
  auto StartTime = chrono::steady_clock::now();
  while(_--){
    // pr();
    solve();
  }   
  auto endTime = chrono::steady_clock::now();
  chrono::duration<double,milli> elapsed = endTime - StartTime;
  cout << elapsed.count() << endl;
  return 0; 
}     
