#define PROGRAM_NAME "program"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define DEBUG 0

#pragma region Definitions
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#endif
#define MOD 1000000007
#define dbgs if (DEBUG)
#define ff first
#define ss second
#define car const auto&
#define ctr(t) const t&
#define var auto
#define pb push_back
#define all(x) x.begin(), x.end()
#define fr(i, a, b) for (int i = a; i < b; i++)
#define fri(i, a, b) for (int i = a; i <= b; i++)
#define frr(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
using str = string;
using ll = long long;
using pll = pair<ll, ll>;
using pi = pair<int, int>;
#pragma endregion

struct Ore {
    int oreCount, robotCount;
};
int costs[4][4];

int solve(int step, Ore params[4], bool bought[4], bool addRobot[4]) {
    dbgs cout << "Step " << step << ": ";
    dbgs fr(i, 0, 4) {
        cout << "(" << params[i].oreCount << "o, " << params[i].robotCount
             << "r) ";
    }
    dbgs cout << endl;
    if (step == 25) return params[3].oreCount;
    int maxGeo = params[3].oreCount;
    fr(i, 0, 4) {
        if (bought[i]) continue;
        bool newAddRobot[4]{0, 0, 0, 0};
        fr(j, 0, 4) {
            if (params[j].oreCount < costs[i][j]) goto cont;
        }
        bought[i] = true;
        newAddRobot[i] = true;
        // cout << "Bought " << i << endl;
        fr(j, 0, 4) { params[j].oreCount -= costs[i][j]; }
        dbgs cout << ">";
        maxGeo = max(maxGeo, solve(step, params, bought, newAddRobot));
        fr(j, 0, 4) { params[j].oreCount += costs[i][j]; }
        bought[i] = false;
    cont:
        continue;
    }
    fr(i, 0, 4) {
        params[i].oreCount += params[i].robotCount;
        if (addRobot[i]) params[i].robotCount++;
    }
    dbgs cout << "!";
    maxGeo = max(maxGeo, solve(step + 1, params, new bool[4]{0, 0, 0, 0},
                               new bool[4]{0, 0, 0, 0}));
    // cout << "-------------------------\n";
    fr(i, 0, 4) {
        if (addRobot[i]) params[i].robotCount--;
        params[i].oreCount -= params[i].robotCount;
    }
    return maxGeo;
}

int main() {
    freopen(PROGRAM_NAME ".in", "r", stdin);
    freopen(PROGRAM_NAME ".out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    fr(i, 0, n) {
        cin >> costs[0][0] >> costs[1][0] >> costs[2][0] >> costs[2][1] >>
            costs[3][0] >> costs[3][2];
        int ans = solve(1, new Ore[4]{{0, 1}, {0, 0}, {0, 0}, {0, 0}},
                        new bool[4]{0, 0, 0, 0}, new bool[4]{0, 0, 0, 0});
        cout << ans << endl;
    }
    return 0;
}