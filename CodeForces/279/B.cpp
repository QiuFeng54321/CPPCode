/*
ID: william234
TASK: B
LANG: C++
*/
#define PROGRAM_NAME "B"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define DEBUG 1
#define USE_FILE 0
#define PARALLEL 1
#if PARALLEL
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#endif
#if USE_FILE
#define rin fin
#define rout fout
#define MAIN_FILE_HEADER                \
    ofstream fout(PROGRAM_NAME ".out"); \
    ifstream fin(PROGRAM_NAME ".in");
#else
#define rin cin
#define rout cout
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

using namespace std;
#define ll long long
ll a[100000];

int main() {
    MAIN_FILE_HEADER
    int n, t;
    rin >> n >> t;
    for (auto i = 0; i < n; i++) {
        rin >> a[i];
        if (i > 0) a[i] += a[i - 1];
    }
    int maxlen = 0;
    int i = 0, j = n - 1;
    while (j >= maxlen) {
        for (i = 0; i <= j - maxlen; i++) {
            if (a[j] - (i > 0 ? a[i - 1] : 0) <= t) {
                maxlen = j - i + 1;
                break;
                // DBGOUT(i << " to " << j << endl)
            }
        }
        j--;
    }
    rout << maxlen << endl;
    return 0;
}