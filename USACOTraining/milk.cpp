/*
ID: william234
TASK: milk
LANG: C++                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int costs[1000] {0};

int main() {
    ofstream fout ("milk.out");
    ifstream fin ("milk.in");
    fill_n(costs, 1000, 0);
    int n, m;
    fin >> n >> m;
    for (auto i = 0; i < m; i++) {
        int cost, amount;
        fin >> cost >> amount;
        costs[cost] += amount;
    }
    int cost, amount;
    for (int costPerUnit = 0; amount < n; costPerUnit++) {
        if (costs[costPerUnit] == 0) continue;
        if (costPerUnit >= 1000) break;
        int increment = min(costs[costPerUnit], n - amount);
        cost += increment * costPerUnit;
        amount += increment;
    }
    fout << cost << endl;
    return 0;
}