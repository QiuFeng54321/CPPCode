/*
ID: william234
TASK: moocast
LANG: C++
*/
#define PROGRAM_NAME "moocast"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <cstring>

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
#if USE_FILE
#define MAIN_FILE_HEADER                     \
    freopen(PROGRAM_NAME ".in", "r", stdin); \
    freopen(PROGRAM_NAME ".out", "w", stdout);
#else
#define MAIN_FILE_HEADER         \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);
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

int N;
vector<vector<int>> adjList;
bool visited[200];
stack<int> trial;
struct node {
    int x, y, p;
};
vector<node> nodes;

int dfs(int i) {
    trial.push(i);
    visited[i] = true;
    int range = 1;
    for (const auto& child : adjList[i]) {
        if (visited[child]) continue;
        range += dfs(child);
        // cout << " " << child << " ";
    }

    trial.pop();
    return range;
}

int main() {
    MAIN_FILE_HEADER
    cin >> N;
    nodes.resize(N);
    adjList.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> nodes[i].x >> nodes[i].y >> nodes[i].p;
    }
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            if (x == y) continue;
            int dx = nodes[x].x - nodes[y].x;
            int dy = nodes[x].y - nodes[y].y;
            if (nodes[x].p * nodes[x].p >= dx * dx + dy * dy) {
                adjList[x].push_back(y);
            }
        }
    }
    int maxRange = 1;
    for (int i = 0; i < N; i++) {
        memset(visited, false, N);
        int range = dfs(i);
        maxRange = max(maxRange, range);
    }
    cout << maxRange << endl;
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