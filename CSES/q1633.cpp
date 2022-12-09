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
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <memory>

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
#define FAST_IO \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);
#if USE_FILE
#define MAIN_FILE_HEADER                     \
    freopen(PROGRAM_NAME ".in", "r", stdin); \
    freopen(PROGRAM_NAME ".out", "w", stdout);\
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

ll d[1000000];

int main() {
    MAIN_FILE_HEADER
    d[0] = 1;
    d[1] = 1;
    d[2] = 2;
    d[3] = 4;
    d[4] = 8;
    d[5] = 16;
    int n;
    cin >> n;
    for (int i = 6; i <= n; i++) {
        d[i] = (d[i - 1] + d[i - 2] + d[i - 3] + d[i - 4] + d[i - 5] + d[i - 6]) % MOD;
    }
    cout << d[n] << endl;
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