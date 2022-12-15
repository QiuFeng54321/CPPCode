/*
ID: william234
TASK: dance_mooves
LANG: C++
*/
#define PROGRAM_NAME "dance_mooves"
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
const int K = 200000;
int n, k;
int a[K], b[K];
int cnt[N];
int idx[N];
int uniquePos = 0;
vector<int> paths[N];
stack<int> path;
int pathLast[N];
bool visited[N];
int ans[N];

void add(int i) {
    for (const auto& e : paths[i]) {
        if (cnt[e] == 0) uniquePos++;
        cnt[e]++;
    }
}
void remove(int i) {
    for (const auto& e : paths[i]) {
        cnt[e]--;
        if (cnt[e] == 0) uniquePos--;
    }
}
int solve(int i) {
    visited[i] = true;
    add(i);
    path.push(i);
    dbgl(i);
    if (!visited[pathLast[i]]) {
        solve(pathLast[i]);
    }
}

int main() {
    MAIN_FILE_HEADER
    cin >> n >> k;
    F0R(i, n) {
        idx[i] = i;
        paths[i].push_back(i);
    }
    F0R(i, k) {
        cin >> a[i] >> b[i];
        a[i]--;
        b[i]--;
        paths[idx[a[i]]].push_back(b[i]);
        paths[idx[b[i]]].push_back(a[i]);
        swap(idx[a[i]], idx[b[i]]);
    }
    F0R(i, n) {
        pathLast[idx[i]] = i;
    }
    F0R(i, n) {
        if (visited[i]) continue;
        solve(i);
        int a = uniquePos;
        while (!path.empty()) {
            auto e = path.top(); path.pop();
            remove(e);
            ans[e] = a;
        }
    }
    F0R(i, n) {
        cout << ans[i] << endl;
    }
    return 0;
}