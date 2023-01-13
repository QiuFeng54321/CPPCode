/*
ID: william234
TASK: E
LANG: C++
*/
#define PROGRAM_NAME "E"
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
#define MOD 1000000007
#define USE_DSU 0
#pragma endregion

#pragma region Definitions
#if defined(__GNUC__) && !defined(__clang__)
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
#define ff first
#define ss second
#define car const auto&
#define ctr(t) const t&
#define var auto
#define all(x) x.begin(), x.end()
#define f0r(i, n) for(int i = 0; i < n; i++)
#define f0ri(i, n) for(int i = 0; i <= n; i++)
#define f1r(i, n) for(int i = 1; i < n; i++)
#define f1ri(i, n) for(int i = 1; i <= n; i++)
using namespace std;
using str = string;
using ll = long long;
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

int t, n, k;
const int N = 400002;
vector<int> adj[N];
int childCount[N];
int age[N];

void solve() {
    f0r(i, n) {
        adj[i].clear();
    }
    memset(childCount, 0, sizeof(childCount));
    memset(age, 0, sizeof(age));
    cin >> n >> k;
    f0r(_, n - 1) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        childCount[u]++;
        childCount[v]++;
    }
    queue<int> process;
    f0r(i, n) {
        if (childCount[i] == 1) {
            age[i] = 1;
            process.push(i);
        }
    }
    while (!process.empty()) {
        var par = process.front(); process.pop();
        for (car child : adj[par]) {
            if (childCount[child] == 1) continue;
            childCount[child]--;
            if (childCount[child] == 1) {
                age[child] = age[par] + 1;
                process.push(child);
            }
        }
    }
    int ans = 0;
    f0r(i, n) {
        if (age[i] > k) ans ++;
    }
    cout << ans << endl;
}

int main() {
    MAIN_FILE_HEADER
    cin >> t;
    f0r(_, t) {
        solve();
    }
    return 0;
}