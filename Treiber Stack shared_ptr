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
class lockFreeStack{
  struct Node{
    T val;
    shared_ptr<Node> next;

    Node(T _val) :val(_val){}
  };
public:
  atomic<shared_ptr<Node>> head{nullptr};

  void push(T val){
    shared_ptr<Node> new_head = make_shared<Node>(val);
    new_head->val = val;
    
    new_head->next = head.load();

    while(!head.compare_exchange_weak(new_head->next,new_head)){

    }

  }

  bool pop(T& result){
    shared_ptr<Node> old_head = head;
    while(old_head){
      if(head.compare_exchange_weak(old_head,old_head->next)){
        result = old_head->val;
        return 1;
      }
    }
    return 0;
  }


  void push_worker(int left,int right){
    for(int i=left;i<=right;i++){
      push(i);
    }
  }

  vector<T> pop_worker(int left,int right,vector<T>& res){
    std::this_thread::sleep_for(std::chrono::microseconds(100));
    for(int i=left;i<=right;i++){
      while(!pop(res[i])){}
    }
    return res;
  }
};




void solve(){

  vector<thread> push;
  vector<thread> pop;
  lockFreeStack<int> lfs;
  vi result(100);
  forn(i,10){
    push.eb(&lockFreeStack<int>::push_worker,&lfs,i*10,(i+1)*10 - 1);
    pop.eb(&lockFreeStack<int>::pop_worker,&lfs,i*10,(i+1)*10 - 1,ref(result));
  }

  forn(i,10){
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
  auto startTime = chrono::steady_clock::now();
  while(_--){
    // pr();
    solve();
  }   
  auto endTime = chrono::steady_clock::now();
  chrono::duration<double,milli> elapsed = endTime-startTime;
  cout << elapsed.count() << endl;
  return 0; 
}     
