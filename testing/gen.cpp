#include "bits/stdc++.h"
 
using namespace std;
 
#define el "\n"
#define faster ios_base::sync_with_stdio(0); cin.tie(0);
#define sq(x) (x)*(x)
#define pb push_back
#define mp make_pair
#define F first
#define S second

random_device rd;
mt19937 rng(rd());
template<typename T> inline T randint(T lo, T hi) { return uniform_int_distribution<T>(lo, hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<T>((int)0, v.size() - 1)(rng)]; } // [lo,hi]

int main() {
        cout << 20 << "\n";
        long long n = 100000;
        long long sum = 0;
        vector<pair<int, int>> k;

        for(int i = 0; i < n; i++) {
                long long profit = randint(1, 10000);
                long long weight = randint(1, 10000);
                k.push_back(make_pair(profit, weight));
                sum += weight;
        }
        long long final = randint(sum/100, sum/10);

        cout << n << " " << final << el;
        for(auto x: k) cout << x.F << " " << x.S << "\n";
}