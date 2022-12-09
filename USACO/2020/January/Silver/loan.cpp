/*
ID: william234
TASK: loan
LANG: C++
*/
#define PROGRAM_NAME "loan"
#include <math.h>

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
#define USE_FILE 1
#define PARALLEL 1
#define MOD 1000000007
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
template <typename T>
T last_true(T lo, T hi, function<bool(T)> f);
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

ll N, K, M;
bool match(ll X) {
    ll G = 0;
    ll day = 0;
    // for (ll day = 0; day < K; day++){
    //     ll Y = max(M, (N - G) / X);
    //     if (Y <= M) {
    //         G += (K - day) * M;
    //         break;
    //     }
    //     G += Y;
    // }
    while (day <= K && G < N) {
        ll Y = (N - G) / X;
        if (Y <= M) {
            day += (N - G + M - 1) / M;
            DBGOUT(X << ": " << day << "\n")
            return day <= K;
        }
        ll max_match = N - X * Y;
        ll days = min((max_match - G) / Y + 1, N - day);
        G += Y * days;
        day += days;
    }
    DBGOUT(X << ": " << day << "\n")
    return G >= N;
}
int main() {
    MAIN_FILE_HEADER
    cin >> N >> K >> M;
    ll ans = last_true<ll>(1LL, __LONG_LONG_MAX__ - 1, match);
    cout << ans << endl;
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