/*
ID: william234
TASK: ${ProgramName}
LANG: C++
*/
#define PROGRAM_NAME "${ProgramName}"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

#pragma region States
#define DEBUG 0
#define USE_FILE 0
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
#pragma endregion

using namespace std;

ll length;
priority_queue<ll, vector<ll>, greater<ll>> q;
int n;
ll cost, temp;

int main() {
    MAIN_FILE_HEADER
    cin >> length >> n;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        q.push(temp);
    }
    for (int i = 1; i < n; i++) {
        auto a = q.top(); q.pop();
        auto b = q.top(); q.pop();
        cost += a + b;
        q.push(a + b);
    }
    cout << cost << endl;
    return 0;
}