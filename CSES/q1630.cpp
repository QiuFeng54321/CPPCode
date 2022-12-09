/*
ID: william234
TASK: TasksAndDeadlines
LANG: C++
*/
#define PROGRAM_NAME "TasksAndDeadlines"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <set>

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
#define MAIN_FILE_HEADER                \
	freopen(PROGRAM_NAME ".in", "r", stdin);\
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
struct task {
    ll a, d;
    bool operator<(const task& b) const {return a < b.a;}
};
task tasks[200000];
int n;
ll reward, curt;
int main() {
    MAIN_FILE_HEADER
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> tasks[i].a >> tasks[i].d;
    }
    sort(tasks, tasks + n, less<task>());
    for (int i = 0; i < n; i++) {
        curt += tasks[i].a;
        reward += tasks[i].d - curt;
        DBGOUT(tasks[i].a << ", " << tasks[i].d << " -> " << reward << ", " << curt << "\n")
    }
    cout << reward << endl;
    return 0;
}