/*
ID: william234
TASK: triangles
LANG: C++
*/
#define PROGRAM_NAME "triangles"
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

const int N = 100000;
const int R = 20002;

int n;
ll xsum[R], ysum[R];
vector<pair<int, int>> coords;
// {{(x|y), i}, ...}
vector<pair<int, int>> todo[R];
// {{xsum, ysum}, ...}
vector<ll> sum[N];

void calcSum() {
    F0R(i, R) {
        if (!todo[i].empty()) {
            dbg(i << ": ");
            sort(todo[i].begin(), todo[i].end());
            ll cur = 0;
            for (const auto& [z, idx] : todo[i]) {
                cur = (cur + z - todo[i][0].f) % MOD;
            }
            F0R(j, todo[i].size()) {
                const auto& [z, idx] = todo[i][j];
                if (j) cur = (cur + (2 * j - todo[i].size()) * (z - todo[i][j - 1].f));
                // 第一次调用push一次（x），第二次y，所以(x, y)
                sum[idx].push_back(cur);
                dbg("(" << z << ", " << cur << ") ");
            }
            dbg("\n")
        }
    }
}

int main() {
    MAIN_FILE_HEADER
    cin >> n;
    coords.resize(n);
    F0R(i, n) {
        cin >> coords[i].f >> coords[i].s;
        coords[i].f += 10000;
        coords[i].s += 10000;
    }
    F0R(i, R) todo[i].clear();
    F0R(i, n) {
        const auto& [x, y] = coords[i];
        todo[x].push_back({y, i});
    }
    calcSum();
    dbgl("Y ---")
    F0R(i, R) todo[i].clear();
    F0R(i, n) {
        const auto& [x, y] = coords[i];
        todo[y].push_back({x, i});
    }
    calcSum();
    ll ans = 0;
    F0R(i, n) {
        dbgs {
            const auto& [x, y] = coords[i];
            dbgl(x << ", " << y << ": " << sum[i][0] << ", " << sum[i][1]);
        }
        ans = (ans + sum[i][0] * sum[i][1]) % MOD;
    }
    cout << ans << endl;
    return 0;
}