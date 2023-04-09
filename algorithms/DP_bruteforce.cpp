#include "bits/stdc++.h"
 
using namespace std;
 
void solve() {
    int iterations; cin >> iterations;
    int n, w;
    cin >> n >> w;
    int cost[n];
    int profit[n];
    for(int i = 1; i <= n; i++) {
        cin >> profit[i] >> cost[i];
    }
    vector<vector<int>> table(n+1, vector<int>(w+1));
    for(int i = 0; i <= n; i++) {
        table[i][0] = 0;
    }
    for(int i = 0; i <= w; i++) {
        table[0][i] = 0;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= w; j++) {
            table[i][j] = table[i-1][j];
            int left = j-cost[i];
            if (left >= 0) {
                table[i][j] = max(table[i][j], table[i-1][left] + profit[i]);
            }
        }
    }
    cout << table[n][w]; 
}   
 
int main() {  
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    solve();
}
