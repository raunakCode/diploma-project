#include "bits/stdc++.h"
 
using namespace std;
 
#define faster ios_base::sync_with_stdio(0); cin.tie(0);
#define sq(x) (x)*(x)
#define all(x) (x).begin(), (x).end()
#define F first
#define S second


random_device rd;
mt19937 rng(rd());
template<typename T> inline T randint(T lo, T hi) { return uniform_int_distribution<T>(lo, hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<T>((int)0, v.size() - 1)(rng)]; } // [lo,hi]

int t = 0;
const int HMS = 20;
int ITEM_COUNT;
int maxWeight;
vector<vector<bool>> harmonies;
vector<pair<int, int>> items;
vector<pair<double, int>> profitDensity;

double HMCR() {
    // initialize value for parameter HMCR in terms of t
    double mx = HMCR_MAX - ((HMCR_MAX-HMCR_MIN)/ITERATIONS)*t;
    return mx;
}

double PAR() {
    // initialize value for parameter PAR in terms of t
    double mx = PAR_MAX - ((PAR_MAX-PAR_MIN)/ITERATIONS)*t;
    return mx;
}

void bernoulli() {
    for(int i = 0; i < HMS; i++) {
        for(int j = 0; j < ITEM_COUNT; j++) {
            // randomly choose 0 or 1 as decision for j'th item in harmony
            int decision = rand()%2;
            harmonies[i].push_back((decision ? 1 : 0));
        }    
    }
}

void REPAIR(vector<bool> &CUR) {
    // calculate total weight of harmony vector
    int weight = 0;
    for(int i = 0; i < ITEM_COUNT; i++) {
        if (CUR[i]) weight += items[i].S;
    }
    if (weight > maxWeight) {
        // DROP phase 
        for(int j = 0; j < ITEM_COUNT; j++) {
            if (CUR[profitDensity[j].S] == 0) {
                continue; 
            }
            CUR[profitDensity[j].S] = 0;
            weight -= items[profitDensity[j].S].S;
            if (weight <= maxWeight) {
                // terminate DROP phase
                break;
            }
        }
    }
    if (weight < maxWeight) {
        // ADD phase
        reverse(all(profitDensity));
        for(int j = 0; j < ITEM_COUNT; j++) {
            // if the item is not included
            if (CUR[profitDensity[j].S] == 0) {
                // check if it fits
                int potentialWeight = weight + items[profitDensity[j].S].S;
                if (potentialWeight <= maxWeight) {
                    weight = potentialWeight;
                    CUR[profitDensity[j].S] = 1;
                }
            }
        }
    }
}

void gen() {
    vector<bool> CUR(ITEM_COUNT);
    for(int i = 0; i < ITEM_COUNT; i++) {
        // TODO: change rng()%2 to double type random for parameter comparisons
        if (rng()%2 <= HMCR()) {
            // choose the corresponding bit in best harmony
            CUR[i] = harmonies[best][i];
        }
        else {
            // choose a harmony x != best -> CUR[i] = x[i];
            int choice = rng()%HMS;
            while(choice == best) choice = rng()%HMS;
            // pitch adjustment
            if (rng()%2 <= PAR()) {
                // flip the bit
                CUR[i] = (CUR[i] ? 0 : 1);
            }
        }
    }
    REPAIR(CUR);
    EVALUATE(CUR);
}


int main() {
    faster
    harmonies.resize(HMS); 
    cin >> ITEM_COUNT >> maxWeight;
    for(int i = 0; i < ITEM_COUNT; i++) {
        int profit, weight;
        cin >> profit >> weight;
        items.push_back(make_pair(profit, weight));
    }
    for(int i = 0; i < ITEM_COUNT; i++) {
        double density = (double)(items[i].F/items[i].S);
        profitDensity.push_back(make_pair(density, i));
    }
    sort(all(profitDensity));
}   