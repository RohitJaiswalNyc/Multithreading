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
double getCurrentTime() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}

// constants
ll oo = 2e18;
int inf = 1e9 + 5;
const int MOD = 1e9+7;
const int N = 4e5 + 5;

// gives the number of matches to the prefix if
// we only take this as ending point of string
void kmp(int n,string s){
	int left[n+10+1][26] = {0};
	int fail[26] = {0};
	forn(i,n){
		int c = s[i] - 'a';
		int previous = left[i][c];
		fail[i+1] = previous;
		left[i][c] = i+1;
		forn(j,26){
			left[i+1][j] = left[previous][j];
		}
	}
}

vector<int> z_func(string &s) {
    int n = s.size(), L = -1, R = -1;
    vector<int> z(n);
    z[0] = n;
    for(int i = 1; i < n; i++) {
        if(i <= R){
        	// 3rd
        	// if updated R value is >= i then
        	// we dont really need to check for
        	// these indexes and just check 
        	// how much i-Lth segment coincides
        	// with the prefix
        	// and R-i+1 gives how much distance
        	// we are from R so the least of both of
        	// them gives me the z for i
        	z[i] = min(z[i - L], R - i + 1);
        }
        while(i + z[i] < n && s[i + z[i]] == s[z[i]])
        	// 1st
        	// this check how much of the segment 
        	// is similiar to the prefix
            z[i]++;
        if(i + z[i] - 1 > R) {
        	// 2nd
        	// this then updates the L and R values
        	// these values are the left and 
        	// right of the subsegment that is 
        	// same as prefix
            L = i;
            R = i + z[i] - 1;
        }
    }
    return z;
}

void solve() {
	
}

int main(){
	startTime = clock();
	#ifndef ONLINE_JUDGE
		freopen("input.txt","r",stdin);
		freopen("1.txt","w",stdout);	
	#endif
	FAST;
	int test = 1;
	cin >> test;
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