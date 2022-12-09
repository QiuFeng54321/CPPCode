/*
ID: william234
TASK: ${ProgramName}
LANG: C++
*/
#define PROGRAM_NAME "${ProgramName}"
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
#define USE_FILE 0
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
#pragma endregion

int n, x;
ll c[1000001][100];
vector<int> weights;

int main() {
    MAIN_FILE_HEADER
    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        int w;
        cin >> w;
        weights.push_back(w);
        for (int wM = 0; wM < n; wM++) {
            if (w > weights[wM]) continue;
            c[w][wM] = 1;
        }
    }
    sort(weights.begin(), weights.end());
    for (int i = 1; i <= x; i++) {
        for (int wM = 0; wM < n; wM++) {
            for (int w = 0; w < n; w++) {
                if (i - w < 0 || weights[w] < weights[wM]) continue;
                c[i][wM] = (c[i][wM] + c[i - weights[w]][w]) % MOD;
            }
        }
    }
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < n; j++) {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
    int ans = 0;
    for (auto& a : c[x]) {
        ans += a;
    }
    cout << ans << endl;
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