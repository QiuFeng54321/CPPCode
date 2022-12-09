/*
ID: william234
TASK: wormsort
LANG: C++
*/
#define PROGRAM_NAME "wormsort"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <iomanip>

#pragma region States
#define DEBUG 0
#define USE_FILE 1
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
T first_true(T lo, T hi, function<bool(T)> f);
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

int n, m;
int cows[100000];
struct Wormhole{
    int a, b;
    ll w;
};
Wormhole worms[100000];


bool solve(ll leastWidth) {
    DSU dsu(n);
    dbgl(leastWidth)
    F0R(i, m) {
        if (worms[i].w < leastWidth) continue;
        dsu.unite(worms[i].a, worms[i].b);
    }
    F0R(i, n) {
        if (!dsu.same_set(i, cows[i])) return false;
    }
    return true;
}

int main() {
    MAIN_FILE_HEADER
    cin >> n >> m;
    F0R(i, n) {
        cin >> cows[i];
        cows[i] --;
    }
    F0R(i, m) {
        cin >> worms[i].a >> worms[i].b >> worms[i].w;
        worms[i].a --;
        worms[i].b --;
    }
    ll res = last_true<ll>(0ll, INT64_MAX - 2, solve);
    cout << (res >= INT64_MAX - 2 ? -1 : res) << endl;
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