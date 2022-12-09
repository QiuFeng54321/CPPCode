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
#else
#define ifdbg(stmt)
#define dbg(stmt)
#define dbgl(stmt)
#endif
#define dbgs if (DEBUG)
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
T first_true(T lo, T hi, function<bool(T)> f);
template <typename T>
T last_true(T lo, T hi, function<bool(T)> f);

#pragma endregion

int n;
// int arr.at(200000);
vector<vector<ll>> res;
ll x;

bool solve(int i) { return res.at(i).back() < x; }

int main() {
    MAIN_FILE_HEADER
    cin >> n;
    F0R(i, n) {
        cin >> x;
        if (i == 0) {
            res.push_back({x});
        } else {
            int firstI = first_true<int>(0, res.size() - 1, solve);
            dbgl(firstI << ": " << x)
            if (firstI == res.size()) res.push_back({x});
            else res.at(firstI).push_back(x);
        }
    }
    for (const auto& i : res) {
        for(const auto& j : i) {
            cout << j << ' ';
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