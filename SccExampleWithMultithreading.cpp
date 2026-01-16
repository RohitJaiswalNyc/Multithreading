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
#include <thread>
#include <future>
#include <sstream>
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
int t = 1;
void pr(){cout << "Case #" << t << ": ";}

struct Scc{
  int n;
  vvi adj,radj;
  vvi comp;
  vi tags;
  vi st;
  vi sz;
  vector<bool> vis;
  Scc(int _n,vvi&& _adj){
    n = _n;
    vis.resize(n);
    tags.resize(n);
    radj.resize(n);
    adj = move(_adj);
    forn(i,n){
      for(auto v:adj[i]){
        radj[v].pb(i);
      }
    }
  }

  Scc(int _n){
    n = _n;
    adj.resize(n);
    radj.resize(n);
    tags.resize(n);
    vis.resize(n);
  }

  ~Scc(){
    adj.clear();
    radj.clear();
    tags.clear();
    vis.clear();
    comp.clear();
    sz.clear();
  }

  void add_edge(int u,int v){
    adj[u].pb(v);
    radj[v].pb(u);
  }
  void dfs(int u,int p){
    for(auto v:adj[u]){
      if(v == p || vis[v]) continue;
      vis[v] = 1;
      dfs(v,u);
    }
    st.pb(u);
  }

  void dfs2(int u,int p){
    tags[u] = sz(comp)-1;
    comp.back().pb(u);
    for(auto v:radj[u]){
      if(v == p || vis[v]) continue;
      vis[v] = 1;
      dfs2(v,u);
    }
  }

  void build(){
    forn(i,n){
      if(!vis[i]){
        vis[i] = 1;
        dfs(i,i);
      }
    }
    
    fill(all(vis),0);
    while(!st.empty()){
      int u = st.back();
      st.pop_back();
      if(vis[u]) continue;
      comp.pb({});
      vis[u] = 1;
      dfs2(u,u);
    }
    sz.resize(sz(comp));
    forn(i,sz(comp)){
      sz[i] = comp[i].size();
    }
  }


};

class ThreadPool {
public:
    ThreadPool(size_t threads) {
        for(size_t i = 0; i < threads; ++i)
            workers.emplace_back([this] {
                for(;;) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this]{ return this->stop || !this->tasks.empty(); });
                        if(this->stop && this->tasks.empty()) return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            });
    }

    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if(stop) throw std::runtime_error("enqueue on stopped ThreadPool");
            tasks.emplace([task](){ (*task)(); });
        }
        condition.notify_one();
        return res;
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for(std::thread &worker: workers) worker.join();
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop = false;
};


string solve_concurrent(int test_id, int n, const vector<int>& inputs) {
    Scc scc(n);
    int ans(0);
    for(int i = 0; i < n; i++) {
        int x = inputs[i];
        int r = (i + x + 1) % n;
        if(i == r) ans++;
        else scc.add_edge(i, r);
    }
    scc.build();
    for(int i = 0; i < n; i++) {
        if(scc.sz[scc.tags[i]] != 1) ans++;
    }

    return to_string(ans) + "\n";
}


int main(){
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("1.txt","w",stdout);  
  #endif
  FAST;
  auto start_time = std::chrono::high_resolution_clock::now();
  int num_tests;
  if (!(cin >> num_tests)) return 0;
  // Determine number of hardware threads available
  unsigned int n_threads = std::thread::hardware_concurrency();
  ThreadPool pool(n_threads == 0 ? 4 : n_threads); 

  vector<future<string>> results;
  results.reserve(num_tests);

  for (int i = 0; i < num_tests; i++) {
      int n; cin >> n;
      vector<int> inputs(n);
      for (int j = 0; j < n; j++) cin >> inputs[j];

      // Queue the test case into the pool
      results.push_back(pool.enqueue(solve_concurrent, i, n, std::move(inputs)));
  }

  // Print results as they finish (or in order)
  for (auto& res : results) {
      cout << res.get();
  }
  auto end_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end_time - start_time;

  // Print the result to stderr (so it doesn't mess up your actual output files)
  cerr << "Total runtime: " << elapsed.count() << " seconds" << endl;
  return 0; 
}     
