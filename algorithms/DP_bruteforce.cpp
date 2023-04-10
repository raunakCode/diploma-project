#include "bits/stdc++.h"
 
#define el "\n"
#define faster ios_base::sync_with_stdio(false); cin.tie(NULL);
#define sq(x) (x)*(x)
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef long double ld;
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define trav(a, x) for (auto &a : x)
 
using namespace std;
 
void solve() {
    int iterations; cin >> iterations;
    int n, k;
    cin >> n >> k;
    int cost[n];
    int profit[n];
    for(int i = 1; i <= n; i++) {
        cin >> profit[i] >> cost[i];
    }
    vector<int> dp1(k+1, 0);
    vector<int> dp2(k+1, 0);
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            dp2[j] = dp1[j];
            int left = j-cost[i];
            if (left >= 0) {
                dp2[j] = max(dp1[left] + profit[i], dp2[j]);
            }
        }
        for(int j = 0; j <= k; j++) {
            dp1[j] = dp2[j];
        }
    }
    cout << dp2[k];
}   
 
int main() {  
    faster
    solve();
}