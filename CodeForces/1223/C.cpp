/*
ID: william234
TASK: 1223C
LANG: C++
*/
#define PROGRAM_NAME "1223C"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
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

#pragma endregion

int q, n;
ll p[100000];
ll pp[100000];
int x, a, y, b;
ll k;

bool solve(ll hi) {
    ll both_count = hi / lcm(a, b);
    ll a_count = max<ll>(hi / a - both_count, 0ll);
    ll b_count = max<ll>(hi / b - both_count, 0ll);
    ll both_up = both_count == 0 ? 0 : pp[both_count - 1];
    ll a_up = a_count == 0 ? both_up : pp[both_count + a_count - 1];
    ll b_up = b_count == 0 ? a_up : pp[both_count + a_count + b_count - 1];
    ll res = both_up * (x + y) +
             max<ll>(0, a_up - both_up) * x +
             max<ll>(0, b_up - a_up) * y;
    dbgl(hi << ": both: " << both_count << ", a: " << a_count << ", b: " << b_count);
    dbgl(both_up << ", " << (a_up - both_up) << ", " << (b_up - a_up))
    dbgl(x << ", " << y << ": " << res)
    return res >= k;
}

void one_case() {
    cin >> n;
    F0R(i, n) { cin >> p[i]; p[i] /= 100; }
    sort(p, p + n, greater<ll>());
    F0R(i, n) {
        pp[i] = p[i];
        if (i != 0) pp[i] += pp[i - 1];
        dbg(pp[i] << ' ')
    }
    dbgl("")
    cin >> x >> a >> y >> b >> k;
    if (a < b) {
        swap(x, y);
        swap(a, b);
    }
    ll ans = first_true<ll>(0, n, solve);
    cout << (ans == n + 1 ? -1 : ans) << endl;
}

int main() {
    MAIN_FILE_HEADER
    cin >> q;
    F0R(i, q) {
        one_case();
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