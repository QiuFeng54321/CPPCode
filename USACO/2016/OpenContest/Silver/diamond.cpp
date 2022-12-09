/*
ID: william234
TASK: diamond
LANG: C++
*/
#define PROGRAM_NAME "diamond"
#include <assert.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define DEBUG 1
#define USE_FILE 1
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
#define ll long long

using namespace std;
int diamonds[50000];
int maxes[50000];
int maxLeft[50001];
int N;
int K;
int l, r;

int main() {
    MAIN_FILE_HEADER
    rin >> N >> K;
    for (int i = 0; i < N; i++) {
        rin >> diamonds[i];
    }
    sort(diamonds, diamonds + N);
    int max1 = 0;
    for (l = 0; l < N; l++) {
        while (r < N) {
            if (diamonds[r] - diamonds[l] > K) break;
            assert(r < N);
            r++;
        }
        int len = r - l;
        maxes[l] = len;
    }
    maxLeft[N] = 0;
    for (r = N - 1; r >= 0; r--) {
        maxLeft[r] = max(maxes[r], maxLeft[r + 1]);
    }
    for (l = 0; l < N; l++) {
        assert(l + maxes[l] <= N);
        max1 = max(max1, maxes[l] + maxLeft[l + maxes[l]]);
    }
    rout << max1 << endl;
    return 0;
}