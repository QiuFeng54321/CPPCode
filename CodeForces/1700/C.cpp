/*
ID: william234
TASK: C
LANG: C++
*/
#define PROGRAM_NAME "C"
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

int t, n;
ll a[200000];

void s2(int i, ll max, ll min, ll& minI) {
    a[i] -= (max - min);
    if (a[i] < a[minI]) minI = i;
}

void solve() {
    cin >> n;
    ll minI = 0, maxI = 0;
    ll ans = 0;
    F0R(i, n) {
        cin >> a[i];
        if (a[i] < a[minI]) minI = i;
        if (a[i] > a[maxI]) maxI = i;
    }
    while (a[minI] != a[maxI]) {
        auto min = a[minI], max = a[maxI];
        ans += (max - min);
        if (minI < maxI) {
            for (int i = maxI; i < n; i++) {
                s2(i, max, min, minI);
            }
            for (int i = maxI; i >= 0; i--) {
                if (a[i] > a[maxI]) maxI = i;
            }
        }
        else {
            for (int i = maxI; i >= 0; i--) {
                s2(i, max, min, minI);
            }
            for (int i = maxI; i < n; i++) {
                if (a[i] > a[maxI]) maxI = i;
            }
        }
        dbgl("ans = " << ans)
        F0R(i, n) {
            dbg(a[i] << ' ')
        }
        dbg('\n')
    }
    ans += abs(a[0]);
    cout << ans << endl;
}

int main() {
    MAIN_FILE_HEADER
    cin >> t;
    F0R(_, t) {
        solve();
    }
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