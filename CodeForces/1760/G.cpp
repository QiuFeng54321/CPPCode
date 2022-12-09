/*
ID: william234
TASK: G
LANG: C++
*/
#define PROGRAM_NAME "G"
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

#pragma region States
#define DEBUG 0
#define USE_FILE 0
#define PARALLEL 1
#define MOD 1000000007
#pragma endregion

#pragma region Definitions
#if defined(__GNUC__) && !defined(__clang__)
#if PARALLEL
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#endif
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
#define ifdbg(stmt) stmt;
#define dbg(stmt) cout << stmt;
#define dbgl(stmt) cout << stmt << endl;
#else
#define ifdbg(stmt)
#define dbg(stmt)
#define dbgl(stmt)
#endif
#define dbgs if (DEBUG)
#define f first
#define s second
#define F0R(i, n) for (int i = 0; i < n; i++)
#define F0Ri(i, n) for (int i = 0; i <= n; i++)
#define F1R(i, n) for (int i = 1; i < n; i++)
#define F1Ri(i, n) for (int i = 1; i <= n; i++)
using namespace std;
using str = string;
using ll = long long;
template <typename T>
T first_true(T lo, T hi, function<bool(T)> f);
template <typename T>
T last_true(T lo, T hi, function<bool(T)> f);

struct DSU {
    vector<int> e;
    DSU(int N) { e = vector<int>(N, -1); }

    // get representive component (uses path compression)
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }

    bool same_set(int a, int b) { return get(a) == get(b); }

    int size(int x) { return -e[get(x)]; }

    bool unite(int x, int y) {  // union by size
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return true;
    }
};
#pragma endregion

ll t, n, a, b, u, v, w;
vector<pair<int, ll>> paths[100000];
typedef set<ll> mt;
mt fromStart;

void xor_dfs(int i, int par, ll curW) {
    if (i == b) return;
    fromStart.insert(curW);
    for (const auto& [c, w] : paths[i]) {
        if (c == par || c == b) continue;
        auto newW = curW ^ w;
        dbgl("From start: " << i << " to " << c << ": " << bitset<16>(newW));
        xor_dfs(c, i, newW);
    }
}
bool xor_dfs2(int i, int par, ll curW) {
    if (i != b && fromStart.count(curW)) {
        return true;
    }
    for (const auto& [c, w] : paths[i]) {
        if (c == par) continue;
        auto newW = curW ^ w;
        dbgl("From end: " << i << " to " << c << ": " << bitset<16>(newW));
        if (xor_dfs2(c, i, newW)) return true;
    }
    return false;
}

int main() {
    MAIN_FILE_HEADER
    cin >> t;
    F0R(_, t) {
        cin >> n >> a >> b;
        a--;
        b--;
        F0R(i, n - 1) {
            cin >> u >> v >> w;
            u--;
            v--;
            paths[u].push_back({v, w});
            paths[v].push_back({u, w});
        }
        xor_dfs(a, -1, 0);
        bool ans = xor_dfs2(b, -1, 0);
        cout << (ans ? "YES" : "NO") << endl;
        F0R(i, n) { paths[i].clear(); }
        fromStart.clear();
    }
    return 0;
}

#pragma region Functions
template <typename T>
T last_true(T lo, T hi, function<bool(T)> f) {
    // if none of the values in the range work, return lo - 1
    lo--;
    while (lo < hi) {
        // find the middle of the current range (rounding up)
        T mid = lo + (hi - lo + 1) / 2;
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
template <typename T>
T first_true(T lo, T hi, function<bool(T)> f) {
    hi++;
    while (lo < hi) {
        T mid = lo + (hi - lo) / 2;
        if (f(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}
#pragma endregion