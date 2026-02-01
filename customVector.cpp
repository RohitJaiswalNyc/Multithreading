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
struct customVector{
  unique_ptr<T[]> array;
  int maxSize;
  int currentSize;

  customVector() noexcept : array(make_unique<T[]>(1)),maxSize(1),currentSize(0) {

  }


  void push_back(T x) noexcept {
    if(currentSize == maxSize){
      unique_ptr<T[]> newArray = make_unique<T[]>(2*maxSize);
      for(int i=0;i<currentSize;i++){
        newArray[i] = move(array[i]);
      }
      maxSize *= 2;
      // cout << "Size Increased " << maxSize << endl;
      array = move(newArray);
    }
    array[currentSize++] = x;

  }

  void shrink_to_fit(){
    int newSize = max(1,currentSize);
    unique_ptr<T[]> newArray = make_unique<T[]>(newSize);
    for(int i=0;i<currentSize;i++){
      newArray[i] = move(array[i]);
    }
    array = move(newArray);
    maxSize = newSize;

  }

  size_t size() const {
    return currentSize;
  }

  bool empty() const noexcept {
    return !currentSize;
  }
  
  T& back() {
    return array[currentSize-1];
  }


  // if you want to save memory when using vector<vector<int>> or vector<string>
  // void pop_back(){
  //   if(currentSize > 0){
  //     currentSize--;
  //     array[currentSize] = T();
  //   }
  // }

  void pop_back(){
    currentSize--;
  }

  void reserve(int newSize) noexcept {
    if(newSize <= maxSize) return;
    unique_ptr<T[]> newArray = make_unique<T[]>(newSize);
    for(int i=0;i<currentSize;i++){
      newArray[i] = move(array[i]);
    }
    maxSize = newSize;
    array = move(newArray);
  }

  T& operator[](const int i) {
    return array[i];
  }

  const T& operator[](const int i) const {
    return array[i];
  }
};

void solve(){
  customVector<int> res;
  int n;
  cin >> n;
  // res.reserve(10);
  forn(i,n){
    int x;
    cin >> x;
    res.pb(x);
    cout << res[i] << " ";
  }
  en;
  cout << res.size() << endl;
  while(!res.empty()){
    cout << res.back() << " ";
    res.pop_back();
  }
  en;
  cout << res.size() << endl;


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
