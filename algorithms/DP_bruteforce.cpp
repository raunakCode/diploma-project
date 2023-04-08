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
    vector<vector<int>> DP(n+1, vector<int>(k+1));
    rep(i, 0, n+1) {
        DP[i][0] = 0;
        DP[0][i] = 0;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= k; j++) {
            // to start with you are gonna have as many pages as possible
            // without having considered the current book
            DP[i][j] = DP[i-1][j];
            // then we are going to see if not taking any book previously beats it
            int left = j-cost[i];
            if (left >= 0) {
                DP[i][j] = max(DP[i][j], DP[i-1][left] + profit[i]);
            }
        }
    }
    cout << DP[n][k]; 
}   
 
int main() {  
    faster
    solve();
}