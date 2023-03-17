#include <bits/stdc++.h>
 
using namespace std;
 
#define sq(x) (x)*(x)
#define all(x) (x).begin(), (x).end()
#define F first
#define S second

random_device rd;
mt19937 rng(rd());
template<typename T> inline T randint(T lo, T hi) { return uniform_int_distribution<T>(lo, hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<T>((int)0, v.size() - 1)(rng)]; } // [lo,hi]

int HMS;
int ITEM_COUNT;
int maxWeight;
int best = 0;
int bestProfit = 0;
int worst;
int t = 0;
const int ITERATIONS = 20;
const double HMCR_MAX = 0.75, HMCR_MIN = 0.25;
const double PAR_MAX = 0.75, PAR_MIN = 0.25;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> WORST;

vector<pair<vector<bool>, int>> harmonies;
vector<pair<int, int>> items;
vector<pair<double, int>> profitDensity;

double HMCR() {
    // initialize value for parameter HMCR in terms of t
    double mx = HMCR_MAX - (double)((double)((HMCR_MAX-HMCR_MIN)*t)/ITERATIONS);
    return mx;
}

double PAR() {
    // initialize value for parameter PAR in terms of t
    double mx = PAR_MAX - (double)((double)((PAR_MAX-PAR_MIN)*t)/ITERATIONS);
    return mx;
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
        reverse(all(profitDensity));
    }
}

void bernoulli() {
    for(int i = 0; i < HMS; i++) {
        for(int j = 0; j < ITEM_COUNT; j++) {
            // randomly choose 0 or 1 as decision for j'th item in harmony
            int decision = rng()%2;
            harmonies[i].F.push_back((decision ? 1 : 0));
        }    
        REPAIR(harmonies[i].F);
        int profit = 0;
        for(int j = 0; j < ITEM_COUNT; j++) {
            if (harmonies[i].F[j] == 1) {
                profit += items[j].F;
            }
        }
        harmonies[i].S = profit;
        if (profit > bestProfit) {
            bestProfit = profit;
            best = i;
        }
        WORST.push(make_pair(profit, i));
    }
}


void EVALUATE(vector<bool> &CUR, int totalProfit) {
    if (totalProfit >= harmonies[best].S) {
        // if CUR harmony is better than best harmony, replace worst with CUR 
        harmonies[best].F = CUR;
    }
    else if (totalProfit >= harmonies[worst].S) {
        // if CUR harmony is better than worst harmony, replace worst with CUR 
        harmonies[worst].F = CUR;
        WORST.pop();
        // switch out worst with CUR harmony in priority queue
        WORST.push(make_pair(totalProfit, worst));
    }
}

void gen() {
    double hmcr = HMCR();
    double par = PAR();

    vector<bool> CUR(ITEM_COUNT);
    int totalProfit = 0;
    for(int i = 0; i < ITEM_COUNT; i++) {
        double rnd = ((double)rng()/(double)4294967295);
        if (rnd <= hmcr) {
            // choose the corresponding bit in best harmony
            CUR[i] = harmonies[best].F[i];
        }
        else {
            // choose a harmony x != best -> CUR[i] = x[i];
            int choice = rng()%HMS;
            while(choice == best) choice = rng()%HMS;
            CUR[i] = harmonies[choice].F[i];
            // pitch adjustment
            rnd = ((double)rng()/(double)4294967295);
            if (rnd <= par) {
                // flip the bit
                CUR[i] = (CUR[i] ? 0 : 1);
            }
        }
        if (CUR[i]) totalProfit += items[i].F;
    }

    REPAIR(CUR);
    EVALUATE(CUR, totalProfit);
}

void DGHS() {
    bernoulli();
    while(t <= ITERATIONS) {
        worst = WORST.top().S;
        gen();
        t += 1;
    }
    // output the bestProfit
    cout << bestProfit;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> HMS >> ITEM_COUNT >> maxWeight;
    harmonies.resize(HMS); 
    for(int i = 0; i < ITEM_COUNT; i++) {
        int profit, weight;
        cin >> profit >> weight;
        items.push_back(make_pair(profit, weight));
    }
    for(int i = 0; i < ITEM_COUNT; i++) {
        double density = ((double)items[i].F/(double)items[i].S);
        profitDensity.push_back(make_pair(density, i));
    }
    sort(all(profitDensity));
    DGHS();
}   
