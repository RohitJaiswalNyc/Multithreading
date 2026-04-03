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
#define sz(a) a.size()
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
 
clock_t startTime;


// constants
ll oo = 2e18;
int inf = 1e9 + 5;
const int MOD = 998244353;
const int N = 2e5 + 5;

int n,m;
string a,b;
vector<int> kmpPre(string s)
{
	int i;
  vector<int> pre(s.size() , 0);
  for (i = 1; i < s.size(); i++) {
      int k = pre[i - 1];
      while (k > 0 && s[i] != s[k]) {
          k = pre[k - 1];
      }
      if (s[k] == s[i])
          k++;
      pre[i] = k;
  }
  
  return pre;
}

void solve(){
  cin >> n >> m;
  cin >> a >> b;
  vector<int> preB = kmpPre(b);
  vector<vector<int>> dp(vector<vector<int>>(m + 1 , vector<int>(n - m + 2 , inf)));
  vector<vector<int>> ndp(vector<vector<int>>(m + 1 , vector<int>(n - m + 2 , inf)));
  dp[0][0] = 0;

  auto getNewPre = [&](char newBit, int pre) {
    auto safeB = [&](int i) {if (i == m) return '#'; return b[i];};
    while (pre > 0 && safeB(pre) != newBit) {
        pre = preB[pre - 1];
    }
    return pre + (b[pre] == newBit);
  };
  for (int i = 0; i < n; i++) {
  	forn(j,m+1) forn(k,n-m+2) ndp[j][k] = inf;
    for (int pre = 0; pre <= m; pre++){
      for(int k = 0; k <= n - m + 1; k++) {
        if (dp[pre][k] < inf) {
          for (char newBit: {'0', '1'}) {
            int newPre = getNewPre(newBit, pre);
            int newK = k + (newPre == m);
            ckmin(ndp[newPre][newK], dp[pre][k] + (int)(a[i] != newBit));
          }
        }
      }
    }
    swap(dp,ndp);
  }

  for (int k = 0; k <= n - m + 1; k++) {
    int sol = inf;
    for (int pre = 0; pre <= m; pre++) {
      sol = min(sol , dp[pre][k]);
    }
    if (sol == inf) {
      cout << "-1 ";
    } else {
      cout << sol << " ";
    }
  } 
  cout << "\n";
}

int main(){
	startTime = clock();
	#ifndef ONLINE_JUDGE
		freopen("input.txt","r",stdin);
		freopen("1.txt","w",stdout);	
	#endif
	FAST;
	int test = 1;
	// cin >> test;
	while(test--){
		solve();
	}		
	return 0;	
}			
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */