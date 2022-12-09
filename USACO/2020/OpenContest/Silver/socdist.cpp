/*
ID: william234
TASK: socdist
LANG: C++
*/
#define PROGRAM_NAME "socdist"
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

int N, M;
pair<ll, ll> intervals[100000];

bool process(int d) {
    int cows = 0;
    int ii = 0;
    ll lastPlace = -d - 1;
    for (; ii < M; ii++) {
        const auto& i = intervals[ii];
        while (max(lastPlace + d, i.first) <= i.second) {
            cows ++;
            lastPlace = max(lastPlace + d, i.first);
        }
        if (cows >= N) break;
    }
    // while (ii < M) {
    //     while (ii < M && intervals[ii].second < lastPlace + d) ii++;
    //     lastPlace = max(intervals[ii].first, lastPlace + d);
    //     cows++;
    //     if (cows >= N) break;
    // }
    return cows >= N;
}

int main() {
    MAIN_FILE_HEADER
    int a, b;
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        intervals[i] = {a, b};
    }
    sort(intervals, intervals + M);
    int i = last_true(1, intervals[M - 1].second, process);
    cout << i << endl;
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