/*
ID: william234
TASK: mootube
LANG: C++
*/
#define PROGRAM_NAME "mootube"
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

vector<pair<int, int>> tree[5001];
bool visited[5001];
int N, Q;

int dfs(int i, int curWeight, int k) {
    visited[i] = true;
    int res = 0;
    for (const auto& p : tree[i]) {
        if (visited[p.first]) continue;
        if (p.second >= k) {
            res ++;
            DBGOUT(i << " to " << p.first << ", w = " << p.second << "\n")
            res += dfs(p.first, min(curWeight, p.second), k);
        }
    }
    DBGOUT(res << " ways from " << i << "\n")
    return res;
}

int main() {
    MAIN_FILE_HEADER
    cin >> N >> Q;
    for (int i = 0; i < N - 1; i++) {
        int p, q, r;
        cin >> p >> q >> r;
        tree[p].push_back({q, r});
        tree[q].push_back({p, r});
    }
    for (int i = 0; i < Q; i++) {
        int k, v;
        cin >> k >> v;
        cout << dfs(v, INT32_MAX, k) << endl;
        memset(visited, 0, N + 1);
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