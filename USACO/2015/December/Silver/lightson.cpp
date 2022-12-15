/*
ID: william234
TASK: lightson
LANG: C++
*/
#define PROGRAM_NAME "lightson"
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
#define USE_FILE 1
#define PARALLEL 1
#define MOD 1000000007
#define USE_DSU 0
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
// Int div a / b with negative result gives upper bound so this is the fix.
ll floorDiv(ll a, ll b) {
    ll val = a / b;
    while (val * b > a) val--;
    return val;
}
#if USE_DSU
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
#endif
#pragma endregion

int ans;
const int N = 100;
int n, m;
bool visited[N][N];
bool lit[N][N];
set<pair<int, int>> toggles[N][N];
set<pair<int, int>> newLits;
set<pair<int, int>> newLits2;
int dx[]{0, 1, 0, -1};
int dy[]{1, 0, -1, 0};

bool reachable(pair<int, int> coord) {
    F0R(i, 4) {
        int x = coord.f + dx[i];
        int y = coord.s + dy[i];
        if (x < 0 || y < 0 || x >= n || y >= n) continue;
        if (lit[x][y] && visited[x][y]) return true;
    }
    return false;
}

void dfs(int x, int y) {
    visited[x][y] = true;
    for (const auto& tgl : toggles[x][y]) {
        if (visited[tgl.f][tgl.s]) continue;
        if (!lit[tgl.f][tgl.s]) {
            lit[tgl.f][tgl.s] = true;
            if (reachable(tgl)) dfs(tgl.f, tgl.s);
        }
    }
    F0R(i, 4) {
        int ex = x + dx[i];
        int ey = y + dy[i];
        if (ex < 0 || ey < 0 || ex >= n || ey >= n) continue;
        if (lit[ex][ey] && !visited[ex][ey]) dfs(ex, ey);
    }
}

int main() {
    MAIN_FILE_HEADER
    cin >> n >> m;
    F0R(i, m) {
        int x, y, a, b;
        cin >> x >> y >> a >> b;
        x--;
        y--;
        a--;
        b--;
        toggles[x][y].insert({a, b});
    }
    lit[0][0] = true;
    dfs(0, 0);
    // bool hasChanges = true;
    // while (hasChanges) {
    //     hasChanges = false;
    //     for (const auto& nlit : newLits) {
    //         if (visited[nlit.f][nlit.s]) continue;
    //         if (reachable(nlit)) {
    //             hasChanges = true;
    //             lit[nlit.f][nlit.s] = true;
    //             dfs(nlit.f, nlit.s);
    //         } else {
    //             newLits2.insert(nlit);
    //         }
    //     }
    //     swap(newLits, newLits2);
    //     newLits2.clear();
    // }
    F0R(i, n) {
        F0R(j, n) {
            ans += lit[i][j];
        }
    }
    cout << ans << endl;
    return 0;
}