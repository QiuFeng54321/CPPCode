/*
ID: william234
TASK: MagicShip
LANG: C++
*/
#define PROGRAM_NAME "MagicShip"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
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
#if PARALLEL && defined(__GNUC__) && !defined(__clang__)
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
#define F0R(i, n) for(int i = 0; i < n; i++)
#define F0Ri(i, n) for(int i = 0; i <= n; i++)
#define F1R(i, n) for(int i = 1; i < n; i++)
#define F1Ri(i, n) for(int i = 1; i <= n; i++)
using namespace std;
using str = string;
using ll = long long;
template<typename T>
T last_true(T lo, T hi, function<bool(T)> f);
template<typename T>
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

ll x1, y1, x2, y2;
int xdir[] {0, 0, -1, 1};
int ydir[] {1, -1, 0, 0};
int n;
int di[100000];
ll xm, ym; // Main x, y dir
ll xo, yo; // Overall in one cycle

int main() {
    MAIN_FILE_HEADER
    cin >> x1 >> y1 >> x2 >> y2;
    xm = x2 > x1 ? 1 : x2 < x1 ? -1 : 0;
    ym = y2 > y1 ? 1 : y2 < y1 ? -1 : 0;
    ll dx = x2 - x1;
    ll dy = y2 - y1;
    cin >> n;
    F0R(i, n) {
        char c;
        cin >> c;
        di[i] = c == 'U' ? 0 : c == 'D' ? 1 : c == 'L' ? 2 : 3;
        if (xdir[di[i]] != xm && ydir[di[i]] != ym) continue;
        if (xdir[di[i]] == xm) {
            yo += ydir[di[i]];
        }
        if (ydir[di[i]] == ym) {
            xo += xdir[di[i]];
        }
    }
    ll cycles = min(dx / xo, dy / yo);
    return 0;
}

#pragma region Functions
template<typename T>
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
template<typename T>
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