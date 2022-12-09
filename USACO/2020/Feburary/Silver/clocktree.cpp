/*
ID: william234
TASK: clocktree
LANG: C++
*/
#define PROGRAM_NAME "clocktree"
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
#include <memory>

#pragma region States
#define DEBUG 0
#define USE_FILE 1
#define PARALLEL 1
#define MOD 1000000007
#pragma endregion

#pragma region Definitions
#if PARALLEL
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#endif
#define FAST_IO \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);
#if USE_FILE
#define MAIN_FILE_HEADER                     \
    freopen(PROGRAM_NAME ".in", "r", stdin); \
    freopen(PROGRAM_NAME ".out", "w", stdout);\
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

int N;
int nodes[2501];
vector<int> graph[2501];
int s0, s1, n0, n1; // Bipartite: Sum and Node count

void dfs(int i, bool col, int parent) {
    if (col) {
        s1 += nodes[i];
        n1 ++;
    } else {
        s0 += nodes[i];
        n0 ++;
    }
    for (const auto& child : graph[i]) {
        if (child == parent) continue;
        dfs(child, !col, i);
    }
}

int main() {
    MAIN_FILE_HEADER
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> nodes[i + 1];
    }
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    dfs(1, false, 1);
    if (s0 % 12 == s1 % 12) { // Equal: all nodes ok
        cout << N;
    } else if (s0 % 12 == (s1 + 1) % 12) {
        cout << n0;
    } else if ((s0 + 1) % 12 == s1 % 12) {
        cout << n1;
    } else {
        cout << 0;
    }
    cout << endl;
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