/*
ID: william234
TASK: milkvisits
LANG: C++
*/
#define PROGRAM_NAME "milkvisits"
#include <algorithm>
#include <bitset>
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

int N, M;
vector<int> paths[100001];
bitset<100001> cows;
bitset<100001> visited;
int components[100001];

int main() {
    MAIN_FILE_HEADER
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        char c;
        cin >> c;
        cows.set(i + 1, c == 'G');
    }
    for (int i = 0; i < N - 1; i++) {
        int x, y;
        cin >> x >> y;
        paths[x].push_back(y);
        paths[y].push_back(x);
    }
    int curComp;
    stack<int> path;
    for (int i = 1; i < N + 1; i++) {
        if (visited[i]) continue;
        visited[i] = true;
        path.push(i);
        components[i] = curComp;
        while (path.size() > 0) {
            auto child = path.top();
            path.pop();
            for (const auto& cc : paths[child]) {
                if (!visited[cc] && cows[cc] == cows[i]) {
                    components[cc] = curComp;
                    visited[cc] = true;
                    path.push(cc);
                }
            }
        }
        curComp++;
    }
    for (int i = 0; i < M; i++) {
        int a, b;
        char c;
        cin >> a >> b >> c;
        visited.reset();
        if (components[a] == components[b]) {
            cout << ((c == 'G') == cows[a]);
        } else {
            cout << 1;
        }
        DBGOUT('\n')
        // cout << (c == 'G' ? res.second.second : res.second.first);
        DBGOUT('\n')
    }
    cout << endl;
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