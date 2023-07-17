/*
ID: william234
TASK: b
LANG: C++
*/
#define PROGRAM_NAME "b"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;
using ll = long long;

const int N = 1501;
int n;
bool dirs[N][N];
int costs[N][N];
int totalCost = 0;
const bool RIGHT = true, DOWN = false;

int getCost(int i, int j) {
    if (costs[i][j]) return costs[i][j];
    if (i == n || j == n) return costs[i][j];
    auto cost = dirs[i][j] == RIGHT ? getCost(i, j + 1) : getCost(i + 1, j);
    costs[i][j] = cost;
    return cost;
}

void updateCost(int i, int j, int cost) {
    totalCost += cost - costs[i][j];
    costs[i][j] = cost;
    if (i > 0 && dirs[i - 1][j] == DOWN) updateCost(i - 1, j, cost);
    if (j > 0 && dirs[i][j - 1] == RIGHT) updateCost(i, j - 1, cost);
}



void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            dirs[i][j] = c == 'R';
        }
        cin >> costs[i][n];
    }
    for (int i = 0; i < n; i++) {
        cin >> costs[n][i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            totalCost += getCost(i, j);
        }
    }
    cout << totalCost << endl;

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        dirs[x][y] ^= 1;
        auto cost = dirs[x][y] == RIGHT ? costs[x][y + 1] : costs[x + 1][y];
        updateCost(x, y, cost);
        cout << totalCost << endl;
    }
}

int main() {
    solve();
    return 0;
}