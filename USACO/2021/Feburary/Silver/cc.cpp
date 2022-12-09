/*
ID: william234
TASK: cc
LANG: C++
*/
#define PROGRAM_NAME "cc"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#pragma region States
#define DEBUG 0
#define USE_FILE 0
#define PARALLEL 1
#pragma endregion

#pragma region Definitions
#if PARALLEL
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#endif
#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);
#if USE_FILE
#define MAIN_FILE_HEADER                       \
    freopen(PROGRAM_NAME ".in", "r", stdin);   \
    freopen(PROGRAM_NAME ".out", "w", stdout); \
    FAST_IO
#else
#define MAIN_FILE_HEADER FAST_IO
#endif
#if DEBUG
#define IFDEBUG(stmt) stmt;
#define DBGOUT(stmt) cout << stmt;
#else
#define IFDEBUG(stmt)
#define DBGOUT(stmt)
#endif
#define ll long long
using namespace std;
int last_true(int lo, int hi, function<bool(int)> f);
int first_true(int lo, int hi, function<bool(int)> f);
#pragma endregion

int N, x, y, c = 0;
int cmap[3000][3000];
set<pair<int, int>> comfortablePairs;
set<pair<int, int>> changedGrids;
int dx[]{0, 1, 0, -1};
int dy[]{1, 0, -1, 0};
// stack<pair<int, int>>

void check(int adjX, int adjY, int selfX, int selfY, int change) {
    if (cmap[adjX][adjY] > 0) {
        bool prevIs4 = cmap[adjX][adjY] == 4;
        if (change == 1) cmap[selfX][selfY] += change;
        cmap[adjX][adjY] += change;
        if (prevIs4 && cmap[adjX][adjY] != 4) {
            comfortablePairs.erase({adjX, adjY});
        }
        if (!prevIs4 && cmap[adjX][adjY] == 4) {
            comfortablePairs.insert({adjX, adjY});
        }
    }
}
void setGrid(int x, int y, int state) {
    cmap[x][y] = state;
    if (x > 0) check(x - 1, y, x, y, state ? 1 : -1);
    if (y > 0) check(x, y - 1, x, y, state ? 1 : -1);
    if (x < 3000) check(x + 1, y, x, y, state ? 1 : -1);
    if (y < 3000) check(x, y + 1, x, y, state ? 1 : -1);
    if (cmap[x][y] == 4) comfortablePairs.insert({x, y});
    else comfortablePairs.erase({x, y});
}
int main() {
    MAIN_FILE_HEADER
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> x >> y;
        x += 1000;
        y += 1000;
        setGrid(x, y, 1);
        c = 0;
        while (comfortablePairs.size() > 0) {
            auto pos = comfortablePairs.begin();

            DBGOUT("pos" << x << ", " << y << endl);
            for (int i = 0; i < 4; i++) {
                int x = pos->first + dx[i];
                int y = pos->second + dy[i];
                if (cmap[x][y] == 0) {
                    setGrid(x, y, 1);
                    changedGrids.insert({x, y});
                    DBGOUT( x << ", " << y << endl);
                    c++;
                    break;
                }
            }
        }
        DBGOUT(c << "\n");
        cout << c << endl;
        for (const auto& pos : changedGrids) {
            setGrid(pos.first, pos.second, 0);
            DBGOUT("change" << pos.first << ", " << pos.second << endl);
        }
        changedGrids.clear();
    }
    return 0;
}

#pragma region Functions
int last_true(int lo, int hi, function<bool(int)> f) {
    // if none of the values in the range work, return lo - 1
    lo--;
    while (lo < hi) {
        // find the middle of the current range (rounding up)
        int mid = lo + (hi - lo + 1) / 2;
        if (f(mid)) {
            // if mid works, then all numbers smaller than mid also work
            lo = mid;
        } else {
            // if mid does not work, greater values would not work either
            hi = mid - 1;
        }
    }
    return lo;
}
int first_true(int lo, int hi, function<bool(int)> f) {
    hi++;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (f(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}
#pragma endregion