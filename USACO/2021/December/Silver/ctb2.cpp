/*
ID: william234
TASK: ctb
LANG: C++
*/
#define PROGRAM_NAME "ctb"
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
#define DEBUG 1
#define USE_FILE 1
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

int T, N, M;

struct vertex {
    int l, r, li;
};
int main() {
    MAIN_FILE_HEADER
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N >> M;
        DSU dsu(N);
        for (int m = 0; m < M; m++) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            dsu.unite(a, b);
        }
        if (dsu.same_set(0, N - 1)) {
            cout << 0 << endl;
            continue;
        }
        vector<vertex> paths;
        F0R(i, N - 1) {
            if (!dsu.same_set(i, i + 1)) {
                paths.push_back({dsu.get(i), dsu.get(i + 1), i});
                dbgl(i << ": " << dsu.get(i) << " -> " << dsu.get(i + 1));
            }
        }
        int ans = 2147483647;
        int i = 0, j = 0;
        while (true) {
            while (j < paths.size() && paths[j].r != dsu.get(N - 1)) j++;
            while (i < paths.size() && paths[i].l != dsu.get(0)) i++;
            if (i == paths.size() || j == paths.size()) break;
            const auto &vi = paths[i], vj = paths[j];
            dbgl("vi: " << vi.l << " -> " << vi.r << " at " << vi.li);
            dbgl("vj: " << vj.l << " -> " << vj.r << " at " << vj.li);

            if (i == j || j - i <= 1) {
                auto sep = (vj.li - vi.li + 1);
                auto half = sep / 2;
                dbgl("Half: " << half) ans = min(
                    ans, sep % 2 == 0 ? (half) * (half)*2
                                      : half * half + (half + 1) * (half + 1));
            } else {
                for (int k = i + 1; k < j; k++) {
                    const auto& vk = paths[k];
                    dbgl("vk: " << vk.l << " -> " << vk.r << " at " << vk.li);
                    ans =
                        min(ans, (vk.li - vi.li + 1) * (vk.li - vi.li + 1) +
                                     (vj.li - vk.li + 1) * (vj.li - vk.li + 1));
                }
            }
            j++;
            i++;
        }
        cout << ans << endl;
    }
    return 0;
}

#pragma region Functions
int last_true(int lo, int hi, function<bool(int)> f) {
    // if none of the values in the range work, return lo - 1
    lo--;
    while (lo < hi) {
        // find the middle of the current range (rounding up)
        int mid = lo + (hi - lo + 1) / 2;
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
int first_true(int lo, int hi, function<bool(int)> f) {
    hi++;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (f(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}
#pragma endregion