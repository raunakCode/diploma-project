#include "bits/stdc++.h"
// #include <ext/pb_ds/assoc_container.hpp>
 
using namespace std;
// using namespace __gnu_pbds;
 
/* typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> indexed_set; */
 
#define el "\n"
#define faster ios_base::sync_with_stdio(0); cin.tie(0);
#define sq(x) (x)*(x)
#define pb push_back
#define mp make_pair
#define F first
#define S second
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<long long, long long> pll;
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, a, b) for (int i = (a); i <= (b); ++i)
#define trav(a, x) for (auto &a : x)

#ifndef ONLINE_JUDGE
#define dbg(x) cerr << #x <<" "; _print(x); cerr << endl;
#else
#define dbg(x)
#endif // ONLINE JUDGE
 
void _print(int t) {cerr << t;}
void _print(ll t) {cerr << t;}
void _print(unsigned long long t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(ld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(bool x) {cerr << (x ? 1 : 0);}
 
template <typename T, typename V> void _print(pair<T, V> &x);
template <typename T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <typename T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <typename T> void _print(const T &x) {int f = 0; cerr << '['; for (auto &i: x) cerr << (f++ ? ", " : ""), _print(i); cerr << "]";}
template <typename T, typename V> void _print(pair<T, V> &x) {cerr << '{'; _print(x.first); cerr << ", "; _print(x.second); cerr << '}';}

random_device rd;
mt19937 rng(rd());
template<typename T> inline T randint(T lo, T hi) { return uniform_int_distribution<T>(lo, hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<T>((int)0, v.size() - 1)(rng)]; } // [lo,hi]

void solve() {
    ll n = 100000;
    cout << 20 << el;
    ll sum = 0;
    vector<pii> k;
    rep(i, 0, n) {
        ll profit = randint(1, 10000);
        ll weight = randint(1, 10000);
        k.pb(mp(profit, weight));
        sum += weight;
    }
    ll final = randint(sum/100, sum/10);
    cout << n << " " << final << el;
    trav(x, k) cout << x.F << " " << x.S << el;
}

int main() {
    faster
    cerr << fixed << setprecision(10);
    // cout << fixed << setprecision(10);
    int test = 1; // cin >> test;
    for(int tc = 1; tc <= test; tc++) {
        solve();
    }
}