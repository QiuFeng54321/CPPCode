/*
ID: william234
TASK: stacking
LANG: C++
*/
#define PROGRAM_NAME "stacking"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#define DEBUG 0
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
int psum[1000000];

int main() {
    MAIN_FILE_HEADER
    int n, k, a, b;
    rin >> n >> k;
    for (int i = 0; i < k; i++) {
        rin >> a >> b;
        psum[a - 1] ++;
        psum[b] --;
    }
    for (int i = 1; i < n; i++) {
        psum[i] += psum[i - 1];
    }
    sort(psum, psum + n);
    rout << psum[n / 2] << endl;
    return 0;
}