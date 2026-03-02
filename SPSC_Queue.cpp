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
#include <immintrin.h>
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

const int cores = 1;
constexpr int RETIRE_THRESHOLD = 1e2;


template<typename T, size_t Size>
class SPSCQueue {
    // We add padding to prevent 'False Sharing' between head and tail
    alignas(64) std::atomic<size_t> head{0};
    alignas(64) std::atomic<size_t> tail{0};
    T buffer[Size];

public:
    bool push(const T& val) {
        size_t t = tail.load(std::memory_order_relaxed);
        size_t h = head.load(std::memory_order_acquire); // See what consumer did

        if ((t + 1) % Size == h) {
            return false; // Queue is full
        }

        buffer[t] = val;
        // Release: ensures the buffer write is visible before the tail update
        tail.store((t + 1) % Size, std::memory_order_release);
        return true;
    }

    bool pop(T& res) {
        size_t h = head.load(std::memory_order_relaxed);
        size_t t = tail.load(std::memory_order_acquire); // See what producer did

        if (h == t) {
            return false; // Queue is empty
        }

        res = buffer[h];
        // Release: ensures the read is finished before head is updated
        head.store((h + 1) % Size, std::memory_order_release);
        return true;
    }
    void producer_thread(int left,int right){
      for(int i=left;i<=right;i++){
        while(!push(i)){
          // _mm_pause();
        }
      }
    }

    void consumer_thread(int left,int right,vi& res){
      for(int i=left;i<=right;i++){
        while(!pop(res[i])){
          // _mm_pause();
        }
      }
    }
};




void solve(){
  vector<thread> push;
  vector<thread> pop;
  push.reserve(cores);
  pop.reserve(cores);
  SPSCQueue<int,100000> hll;
  vi result(cores*100000);
  forn(i,cores){
    push.eb(&SPSCQueue<int,100000>::producer_thread,&hll,i*100000,(i+1)*100000 - 1);
    pop.eb(&SPSCQueue<int,100000>::consumer_thread,&hll,i*100000,(i+1)*100000 - 1,ref(result));
  }

  forn(i,cores){
    push[i].join();
    pop[i].join();
  }
  
  // for(int &x:result) cout << x << " ";
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
  auto startTime = chrono::steady_clock::now();
  forn(i,_){
    // pr();
    solve();
  }
  auto endTime = chrono::steady_clock::now();
  chrono::duration<double,milli> elapsed = endTime-startTime;
  cout << elapsed.count()/_ << endl;
  return 0; 
}     
