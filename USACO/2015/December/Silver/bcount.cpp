/*
ID: william234
TASK: bcount
LANG: C++
*/
#define PROGRAM_NAME "bcount"
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
#define dbgs if (DEBUG)
#else
#define ifdbg(stmt)
#define dbg(stmt)
#define dbgs
#endif
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

int N, Q;
int psums[100001][3];
int main() {
    MAIN_FILE_HEADER
    cin >> N >> Q;
    F1Ri(i, N) {
        int type;
        cin >> type;
        psums[i][--type] ++;
        F0R(j, 3) {
            psums[i][j] += psums[i - 1][j];
        }
    }
    F0R(i, Q) {
        int a, b;
        cin >> a >> b;
        F0R(j, 3) {
            int count = psums[b][j] - psums[a - 1][j];
            cout << count;
            if (j != 2) cout << ' ';
        }
        cout << endl;
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