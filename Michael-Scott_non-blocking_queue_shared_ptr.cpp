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


template<typename T>
class LockFreeQueue{
private:  
  struct Node{
    atomic<shared_ptr<Node>> next;
    T val;
    Node(): next(nullptr), val(T()){}
    Node(T _val): next(nullptr), val(_val){}
  };
  atomic<shared_ptr<Node>> head,tail;


public:
  bool finished;
  LockFreeQueue(): finished{0} {
    shared_ptr<Node> dummy = make_shared<Node>(-1);
    head = dummy,tail = dummy;
  }

  void enqueue(T val){
    shared_ptr<Node> new_node = make_shared<Node>(val);
    while(true){
      shared_ptr<Node> last = tail.load();
      shared_ptr<Node> next = last->next.load();
      if(last == tail.load()){
        if(next == nullptr){
          if(last->next.compare_exchange_weak(next,new_node)){
            tail.compare_exchange_weak(last,new_node);
            return;
          }
        }
        else{
          // update tail
          tail.compare_exchange_weak(last,next);
        }
      }
    }
  }

  // make this bool after checking enqueue
  bool dequeue(T& result){
    while(true){
      shared_ptr<Node> h = head.load();
      shared_ptr<Node> t = tail.load();
      shared_ptr<Node> next = h->next.load();
      if(h == head.load()){
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
              return 0;
            }
            else{
              // this_thread::sleep_for(chrono::microseconds(1000));
              continue;
            }

          }
          else{
            tail.compare_exchange_weak(t,next);
          }
        }
        else{
          if(next){
            result = next->val;
            if(head.compare_exchange_weak(h,next)){
              return 1;
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

  void consumer_thread(int left,int right,vi& res){
    for(int i=left;i<=right;i++){
      dequeue(res[i]);
    }
  }
};


void solve(){
  LockFreeQueue<int> lfq;
  vector<thread> prod,cons;
  vi res(100);
  forn(i,10){
    prod.eb(&LockFreeQueue<int>::producer_thread,&lfq,i*10,(i+1)*10-1);
    cons.eb(&LockFreeQueue<int>::consumer_thread,&lfq,i*10,(i+1)*10-1,ref(res));
  }

  forn(i,10){
    if(prod[i].joinable()) prod[i].join();
  }
  lfq.finished = 1;
  forn(i,10){
    if(cons[i].joinable()) cons[i].join();
  }

  for(auto &x:res){
    cout << x << " ";
  }
  en;
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
