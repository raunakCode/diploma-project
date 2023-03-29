#include "bits/stdc++.h"
 
using namespace std;
 
#define sq(x) (x)*(x)
#define all(x) (x).begin(), (x).end()
#define F first
#define S second

random_device rd;
mt19937 rng(rd());
template<typename T> inline T randint(T lo, T hi) { return uniform_int_distribution<T>(lo, hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<T>((int)0, v.size() - 1)(rng)]; } // [lo,hi]

int BINVEC;
int ITEM_COUNT;
int maxWeight;
int best = 0;
int bestProfit = 0;
int worst;
int k = 1;
// Initially, 3 STDEVs should roughly equal ITEM_COUNT
double STDEV;
int t = 1;
const int ITERATIONS = 20;

vector<pair<vector<bool>, int>> solutions;
vector<pair<int, int>> items;
vector<pair<int, int>> weightSort;
vector<pair<double, int>> profitDensity;
multiset<pair<int, int>> WORST;

int getFlips() {
    // TODO: check whether this works for higher ITEM_COUNT
    // initialize value for parameter HMCR in terms of t
    double curSpace = (double)ITEM_COUNT/(double)3;
    STDEV = ((double)t/(double)ITERATIONS) * (curSpace);
    mt19937 generator(rd());
    // TODO: choose a random x value and get the normal distribution value for it 
        // TODO: check whether this actually gets decimal values
    double mean = 0;
    normal_distribution<double> normal(mean, STDEV);    
    double k = normal(generator); 
    int m = int(ceil(k)); 
    return m;
}

int REPAIR(vector<bool> &CUR, int totalProfit) {
    int weight = 0, temp;

    for(int i = 0; i < ITEM_COUNT; i++) {
        if (CUR[i]) weight += items[i].S;
    }
    //check if weight = maxWeight -> no repair
    if (weight == maxWeight) return totalProfit;

    vector<pair<double, int>> itemDensity; 
    vector<pair<int, int>> itemWeight;
    // make a vector with chosen items in CUR binary vector
    for(int i = 0; i < ITEM_COUNT; i++) {
        if (CUR[i] == 1) {
            itemDensity.push_back(profitDensity[i]);
            itemWeight.push_back(weightSort[i]);
        }
    }
    sort(all(itemDensity), greater<pair<double, int>>());
    sort(all(itemWeight));
    if (weight > maxWeight) {
        // Stage 1: Density first stage 
        weight = 0;
        temp = 0;
        int i = 0;
        while(temp < maxWeight && i < itemDensity.size()) {
            weight = temp;
            temp += items[itemDensity[i].S].S;
            i++;
            if (temp > maxWeight) {
                i--;
                break;
            }
        }
        for(int j = i; j < itemDensity.size(); j++) {
            int index = itemDensity[j].S;
            CUR[index] = 0;
            totalProfit -= items[index].F;
        }
    }
    // Stage 2: Minimum weight first stage
    int i = 0;
    while(weight < maxWeight && i < itemWeight.size()) {
        if (CUR[itemWeight[i].S] == 0 && weight + items[itemWeight[i].S].S <= maxWeight) {
            CUR[itemWeight[i].S] = 1;
            totalProfit += items[itemWeight[i].S].F;
            weight += items[itemWeight[i].S].S;
        }
        else break;
        i++;
    }
    return totalProfit;
}

void bernoulli() {
    for(int i = 0; i < BINVEC; i++) {
        int profit = 0;
        for(int j = 0; j < ITEM_COUNT; j++) {
            int choice = rng()%2;
            solutions[i].F.push_back((choice ? 1 : 0));
            if (choice == 1) profit += items[j].F; 
        }
        profit = REPAIR(solutions[i].F, profit);
        solutions[i].S = profit;
        if (profit > bestProfit) {
            bestProfit = profit;
            best = i;
        }
        WORST.insert(make_pair(profit, i));
    } 
}

bool EVALUATE(vector<bool> &CUR, int totalProfit) {
    if (totalProfit >= solutions[best].S) {
        solutions[best].F = CUR;
        solutions[best].S = totalProfit;
        auto it = prev(WORST.end());
        WORST.erase(it);
        WORST.insert(make_pair(totalProfit, best));
        return 1;
    }
    else if (totalProfit >= solutions[(*WORST.begin()).S].S) {
        solutions[(*WORST.begin()).S].F = CUR;
        WORST.erase(WORST.begin()); 
        WORST.insert(make_pair(totalProfit, worst));
        return 1;
    }
    return 0;
}

vector<bool> gen(bool &ret) {
    vector<bool> CUR = solutions[(*WORST.begin()).S].F;
    int curProfit = (*WORST.begin()).F;
    int flips = getFlips();
    flips %= ITEM_COUNT;
    int flipCount = 0;
    int i = rng()%ITEM_COUNT;
    // flipping some number of bits
    while(flipCount < flips) {
        if (CUR[i] == 0) {
            CUR[i] = 1;
            curProfit += items[i].F;
        }
        else {
            CUR[i] = 0;
            curProfit -= items[i].F;
        }
        i += (flips < 0 ? -1 : 1);     
        if (i == -1) i = ITEM_COUNT-1;
        else if (i == ITEM_COUNT) i = 0;
        flipCount++;
    } 
    // mutate one bit toward optimal
    // (p = 1 gives slow mutations toward current optimal allowing for diversity)
    int bit = rng()%ITEM_COUNT;
    if (CUR[bit] != solutions[best].F[bit]) {
        curProfit += (CUR[bit] == 0 ? items[i].F : -items[i].F);
    }

    // repair
    curProfit = REPAIR(CUR, curProfit);
    // evaluate 
    ret = EVALUATE(CUR, curProfit);
    return CUR;
}

void BMQHOA() {
    bernoulli();
    while(t <= ITERATIONS) {
        worst = (*WORST.begin()).S;
        bool stable = 0;
        while(stable == 0) {
            bool ret = 0;
            vector<bool> CUR = gen(ret);
            if (ret == 1) stable = 1;    
        }
        t++;
    }
    // output best profit;
    cout << solutions[best].S;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> BINVEC >> ITEM_COUNT >> maxWeight;
    solutions.resize(BINVEC);
    for(int i = 0; i < ITEM_COUNT; i++) {
        int profit, weight;
        cin >> profit >> weight;
        items.push_back(make_pair(profit, weight));
        weightSort.push_back(make_pair(weight, i));
    }
    sort(all(weightSort));
    //TODO: make (density, i) in profitDensity into (density) if able to
    for(int i = 0; i < ITEM_COUNT; i++) {
        double density = ((double)items[i].F/(double)items[i].S);
        profitDensity.push_back(make_pair(density, i)); 
    }
    BMQHOA();
}   