/*
ID: william234
TASK: StudyingAlgo
LANG: C++
*/
#define PROGRAM_NAME "StudyingAlgo"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>


#define DEBUG 0
#define USE_FILE 0
#define PARALLEL 1
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

using namespace std;

int n, x;
int a[10000];


int main() {
    MAIN_FILE_HEADER
    cin >> n >> x;
    int tmp;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a + n);
    int i = 0;
    while (i < n && x - a[i] >= 0) {
        x -= a[i++];
    }
    cout << i << endl;
    return 0;
}