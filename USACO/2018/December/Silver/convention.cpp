/*
ID: william234
TASK: convention
LANG: C++
*/
#define PROGRAM_NAME "convention"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

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

int N, M, C;
int t[100000];

// struct Slice {
//     int start, end;
//     int len() const {return t[end] - t[start];}
//     bool operator<(const Slice& r) const {
//         return len() < r.len();
//     }
// };

// multiset<Slice, less<Slice>> slices;

bool process(int maxTime) {
    int i = 0, j = 0, busCount = 0;
    DBGOUT(maxTime << ": \n");
    while (j < N) {
        if (t[j] - t[i] > maxTime || (j - i + 1) > C) {
            DBGOUT(i << ", " << j << "\n")
            i = j;
            busCount++;
            // if (busCount > M) return false;
        } else {
            j++;
            if (j == N) {
                DBGOUT(i << ", " << j << "\n")
                busCount++;
            }
        }
    }
    return busCount <= M;
}

int main() {
    MAIN_FILE_HEADER
    cin >> N >> M >> C;
    for (int i = 0; i < N; i++) {
        cin >> t[i];
    }
    sort(t, t + N);
    int res = first_true(1, INT32_MAX - 1, process);
    cout << res << endl;
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