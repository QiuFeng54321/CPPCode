/*
ID: william234
TASK: countcross
LANG: C++
*/
#define PROGRAM_NAME "countcross"
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
#define USE_FILE 1
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

int K, N, R;
bool grid[100][100][6];  // 4: cow, 5: occupied
vector<int> regions;
int rsum, ans;
int xdir[]{0, 1, 0, -1};
int ydir[]{1, 0, -1, 0};
stack<pair<int, int>> path;

int main() {
    MAIN_FILE_HEADER
    cin >> N >> K >> R;
    for (int i = 0; i < R; i++) {
        int x1, y1, x2, y2, dx, dy;
        cin >> x1 >> y1 >> x2 >> y2;
        dx = x2 - x1;
        dy = y2 - y1;
        for (int j = 0; j < 4; j++) {
            if (dx == xdir[j] && dy == ydir[j]) {
                grid[x1 - 1][y1 - 1][j] = true;
                grid[x2 - 1][y2 - 1][(j + 2) % 4] = true;
                break;
            }
        }
    }
    for (int i = 0; i < K; i++) {
        int x, y;
        cin >> x >> y;
        grid[x - 1][y - 1][4] = true;
    }
    int regionPtr = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j][5]) continue;
            int regionCows = 0;
            path.push({i, j});
            grid[i][j][5] = true;
            if (grid[i][j][4]) regionCows++;
            while (path.size() != 0) {
                auto child = path.top();
                path.pop();
                for (int d = 0; d < 4; d++) {
                    if (grid[child.first][child.second][d]) continue;
                    int x = child.first + xdir[d];
                    int y = child.second + ydir[d];
                    if (x < 0 || x >= N || y < 0 || y >= N) continue;
                    if (grid[x][y][5]) continue;
                    if (grid[x][y][4]) regionCows++;
                    grid[x][y][5] = true;
                    path.push({x, y});
                }
            }
            DBGOUT(regionCows << "\n")
            ans += rsum * regionCows;
            rsum += regionCows;
        }
    }
    DBGOUT(rsum << " " << ans << "\n")
    cout << ans << endl;
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