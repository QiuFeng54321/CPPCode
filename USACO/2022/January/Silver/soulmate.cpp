/*
ID: william234
TASK: soulmate
LANG: C++
*/
#define PROGRAM_NAME "soulmate"
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

int N;
// 11111 => 01101:
// 11111 => 100000 => 10000 => 1000 => 1001 => 1010 => 1011 => 1100 => 1101
// 01010 => 11000:
// 
int main() {
    MAIN_FILE_HEADER
    cin >> N;
    for (int i = 0; i < N; i++) {
        ll a, b, c = 0;
        cin >> a >> b;
        while (a != b) {
            if (a > b) {
                if (a % 2 == 0) {
                    a --;
                    c ++;
                }
                a >>= 1;
                c++;
            } else {
                if (a > (b >> 1)) {
                    c += a - (b >> 1);
                    a = b >> 1;
                } else {
                    int ta = a, tb = b, width = 0;
                    while (true) {
                        ta >>= 1;
                        tb >>= 1;
                        if (!tb) break;
                        if (!ta) width ++;
                    }
                }
            }
        }
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