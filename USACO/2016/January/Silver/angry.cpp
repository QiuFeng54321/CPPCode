/*
ID: william234
TASK: angry
LANG: C++
*/
#define PROGRAM_NAME "angry"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <functional>

#pragma region States
#define DEBUG 0
#define USE_FILE 1
#define PARALLEL 1
#pragma endregion

#pragma region Definitions
#if PARALLEL
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#endif
#if USE_FILE
#define MAIN_FILE_HEADER                     \
    freopen(PROGRAM_NAME ".in", "r", stdin); \
    freopen(PROGRAM_NAME ".out", "w", stdout);
#else
#define MAIN_FILE_HEADER         \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);
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

int N, K;
int x[50000];

bool process(int r) {
    int i = 0, j = 0;
    int shots = 0;
    while (j < N) {
        while (j < N && x[j] <= x[i] + 2 * r) j++;
        i = j;
        shots++;
    }
    return shots <= K;
}

int main() {
    MAIN_FILE_HEADER
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> x[i];
    }
    sort(x, x + N);
    int r = first_true(0, x[N - 1] - x[0], process);
    cout << r << endl;
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