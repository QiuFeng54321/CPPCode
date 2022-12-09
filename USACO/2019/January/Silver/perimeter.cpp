/*
ID: william234
TASK: perimeter
LANG: C++
*/
#define PROGRAM_NAME "perimeter"
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

bool config[1002][1002];
bool visited[1002][1002];
stack<pair<int, int>> path;
int N;
int xdir[] {0, 1, 0, -1};
int ydir[] {1, 0, -1, 0};
int minP, maxA;

int main() {
    MAIN_FILE_HEADER
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            char inp;
            cin >> inp;
            config[i][j] = inp == '#';
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (visited[i][j] || !config[i][j]) continue;
            path.push({i, j});
            visited[i][j] = true;
            int peri = 0, area = 1;
            while (path.size() != 0) {
                auto top = path.top();
                path.pop();
                for (int di = 0; di < 4; di++) {
                    int x = top.first + xdir[di];
                    int y = top.second + ydir[di];
                    if (x < 0 || x > N + 1 || y < 0 || y > N + 1) continue;
                    if (config[x][y] && !visited[x][y]) {
                        visited[x][y] = true;
                        path.push({x, y});
                        area ++;
                    } 
                    else if (!config[x][y]) {
                        peri ++;
                        DBGOUT("Perimeter: " << x << ", " << y << "\n");
                    }
                }
            }
            if (area > maxA) {
                maxA = area;
                minP = peri;
            } else if (area == maxA && peri < minP) {
                minP = peri;
            }
        }
    }
    cout << maxA << ' ' << minP << endl;

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