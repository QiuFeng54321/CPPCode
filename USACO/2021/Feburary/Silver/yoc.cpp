/*
ID: william234
TASK: yoc
LANG: C++
*/
#define PROGRAM_NAME "yoc"
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

int N, K;
int ancestors[65536];

struct sep {
    int len, next;
    bool operator <(const sep& s2) const { return next < s2.next; }
};

vector<sep> seps;

int main() {
    MAIN_FILE_HEADER
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> ancestors[i];
    }
    sort(ancestors, ancestors + 65536, greater<int>());
    int last;
    for (int i = 0; i < N; i++) {
        int lower = ancestors[i] / 12 + 1;
        DBGOUT(lower << ", " << last << "\n")
        if (i == 0) {
            last = lower;
            seps.push_back({1, 0});
            continue;
        }
        if (lower == last) continue;
        if (lower + 1 == last) {
            seps.back().len++;
        } else {
            seps.back().next = last - lower;
            seps.push_back({1, 0});
        }
        last = lower;
    }
    sort(seps.begin(), seps.end(), less<sep>());
    int ans = 0;
    for (const auto& s : seps) {
        DBGOUT(s.len << ", " << s.next << "\n")
        if (N < seps.size()) {
            ans += s.next;
            N--;
        }
        ans += s.len;
    }
    cout << (ans * 12) << endl;
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