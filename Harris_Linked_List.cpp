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

template<typename T>
struct Node{
  T data;
  atomic<Node*> next;
  Node(T val): data(val),next(nullptr){}
};


template<typename T>
class Harris_LL{
private:
  Node<T>* head;

public:

  Harris_LL(): head(new Node<T>(T())){}

  bool is_marked(Node<T>* ptr) {
    return (reinterpret_cast<uintptr_t>(ptr) & 1) != 0;
  }

  Node<T>* get_unmarked(Node<T>* ptr) {
    return reinterpret_cast<Node<T>*>(reinterpret_cast<uintptr_t>(ptr) & ~1);
  }

  Node<T>* get_marked(Node<T>* ptr) {
    return reinterpret_cast<Node<T>*>(reinterpret_cast<uintptr_t>(ptr) | 1);
  }

  bool find(const T& key,Node<T>*& prv, Node<T>*& curr){
    Node<T>* next = nullptr;
  retry:
    prv = head;
    curr = prv->next.load();

    while(1){
      if(curr == nullptr) return 0;

      next = curr->next.load();

      if(is_marked(next)){
        if(!prv->next.compare_exchange_weak(curr,get_unmarked(next))){
          goto retry;  
        }
        curr = get_unmarked(next);
        continue;      
      }

      if(curr->data >= key){
        return (curr->data == key);
      }
      prv = curr;
      curr = next;
    }

  }

  bool insert(T val){
    Node<T>* new_node = new Node<T>(val);
    Node<T> *prv,*cur;

    while(1){
      if(find(val,prv,cur)){
        delete new_node;
        return 0;
      }
      new_node->next.store(cur);
      if(prv->next.compare_exchange_weak(cur,new_node)){
        return 1;
      }
    }
  }

  bool remove(T val,T& res,int tid){
    Node<T> *prv,*cur,*next;
    while(1){
      if(!find(val,prv,cur)) return 0;
      next = cur->next.load();
      if(is_marked(next)) continue;

      if(!cur->next.compare_exchange_weak(next,get_marked(next))){
        continue;
      }

      prv->next.compare_exchange_weak(cur,next);
      res = cur->data;
      return 1;
    }
  }

  void push_worker(int left,int right){
    for(int i=left;i<=right;i++){
      insert(i);
    }
  }

  void pop_worker(int tid, int left,int right,vector<T>& res){
    std::this_thread::sleep_for(std::chrono::microseconds(100));
    for(int i=left;i<=right;i++){
      remove(i,res[i],tid);
    }
  }

};




void solve(){
  vector<thread> push;
  vector<thread> pop;
  push.reserve(cores);
  pop.reserve(cores);
  // hazardManager<int> mgr;
  Harris_LL<int> hll;
  vi result(cores*100);
  forn(i,cores){
    push.eb(&Harris_LL<int>::push_worker,&hll,i*100,(i+1)*100 - 1);
    pop.eb(&Harris_LL<int>::pop_worker,&hll,i,i*100,(i+1)*100 - 1,ref(result));
  }

  forn(i,cores){
    push[i].join();
    pop[i].join();
  }
  
  for(int &x:result) cout << x << " ";
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
  while(_--){
    // pr();
    solve();
  }   
  return 0; 
}     
