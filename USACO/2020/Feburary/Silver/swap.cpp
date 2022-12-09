/*
ID: william234
TASK: swap
LANG: C++
*/
#define PROGRAM_NAME "swap"
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
int last_true(int lo, int hi, function<bool(int)> f);
int first_true(int lo, int hi, function<bool(int)> f);
#pragma endregion

int N, M, K;
#define C 100001
int c0[C], c1[C];
int T[C];
int l[100], r[100];

int main() {
    MAIN_FILE_HEADER
    cin >> N >> M >> K;
    for (int i = 0; i < M; i++) {
        cin >> l[i] >> r[i];
        l[i]--;
        r[i]--;
    }
    for (int i = 0; i < N; i++) {
        c0[i] = i;
        int k = i;
        for (int j = 0; j < M; j++) {
            if (l[j] <= k && k <= r[j]) {
                k = l[j] + r[j] - k;
            }
        }
        c1[k] = i;
    }
    for (int i = 0; i < N; i++) {
        DBGOUT(c1[i] << " ");
        T[c1[i]] = c0[i];
    }
    DBGOUT("\n")
    for (int i = 0; i < N; i++) {
        DBGOUT(T[i] << " ")
    }
    DBGOUT("\n")
    K %= N;
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            c1[T[j]] = c0[j];
        }
        for (int j = 0; j < N; j++) {
            DBGOUT(c1[j] << " ")
        }
        DBGOUT("\n")
        memcpy(c0, c1, N * sizeof(int));
    }
    for (int i = 0; i < N; i++) {
        cout << (c1[i] + 1) << endl;
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