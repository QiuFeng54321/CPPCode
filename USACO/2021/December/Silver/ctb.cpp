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
#include <iostream>
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
int last_true(int lo, int hi, function<bool(int)> f);
int first_true(int lo, int hi, function<bool(int)> f);

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
        int i = -1, j = -1, min_sep = INT32_MAX;
        for (int k = 0; k < N; k++) {
            if (dsu.same_set(k, 0)) {
                i = k;
                if (j != -1) min_sep = min(min_sep, abs(j - i));
                DBGOUT("i: " << i << ", " << min_sep << "\n")
            }
            if (dsu.same_set(k, N - 1)) {
                j = k;
                if (i != -1) min_sep = min(min_sep, abs(j - i));
                DBGOUT("j: " << j << ", " << min_sep << "\n")
            }
        }
        int half = min_sep / 2;
        if (min_sep == 1)
            cout << 1 << endl;
        else if (min_sep % 2 == 1)
            cout << ((half) * (half) +
                     (half + 1) * (half + 1))
                 << endl;
        else
            cout << (half * half * 2) << endl;
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