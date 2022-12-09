/*
ID: william234
TASK: fenceplan
LANG: C++
*/
#define PROGRAM_NAME "fenceplan"
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

int N, M;
vector<int> adjList[100000];
pair<int, int> coords[100000];
bool visited[100000];

typedef pair<pair<int, int>, pair<int, int>> pp;

pp maxpp(pp a, pp res) {
    pp r{};
    r.first.first = max(a.first.first, res.first.first);
    r.first.second = max(a.first.second, res.first.second);
    r.second.first = min(a.second.first, res.second.first);
    r.second.second = min(a.second.second, res.second.second);
    return r;
}

pp dfs(int i) {
    auto r = pair{coords[i], coords[i]};
    visited[i] = true;
    for (const auto& child : adjList[i]) {
        if (visited[child]) continue;
        auto res = dfs(child);
        r = maxpp(r, res);
    }
    return r;
}

int perimeter(pp p) {
    return 2 * (p.first.first - p.second.first + p.first.second - p.second.second);
}

int main() {
    MAIN_FILE_HEADER
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> coords[i].first >> coords[i].second;
    }
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        adjList[a - 1].push_back(b - 1);
        adjList[b - 1].push_back(a - 1);
    }
    int minP = INT32_MAX;
    for (int i = 0; i < N; i++) {
        if (visited[i]) continue;
        auto r = dfs(i);
        minP = min(minP, perimeter(r));
        DBGOUT(r.second.first << ", " << r.second.second << " to " << r.first.first << ", " << r.first.second << "\n")
    }
    cout << minP << endl;

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