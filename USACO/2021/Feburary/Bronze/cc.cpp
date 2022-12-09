/*
ID: william234
TASK: cc
LANG: C++
*/
#define PROGRAM_NAME "cc"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define DEBUG 0
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
#define ll long long

using namespace std;

int N, x, y, c = 0;
int cmap[1001][1001];

void check(int adjX, int adjY, int selfX, int selfY) {
    if (cmap[adjX][adjY] > 0) {
        bool prevIs4 = cmap[adjX][adjY] == 4;
        cmap[selfX][selfY]++;
        cmap[adjX][adjY]++;
        if (prevIs4 && cmap[adjX][adjY] != 4) {
            c--;
        }
        if (!prevIs4 && cmap[adjX][adjY] == 4) {
            c++;
        }
    }
}
int main() {
    MAIN_FILE_HEADER
    rin >> N;
    for (int i = 0; i < N; i++) {
        rin >> x >> y;
        cmap[x][y] = 1;
        if (x > 0) check(x - 1, y, x, y);
        if (y > 0) check(x, y - 1, x, y);
        if (x < 1001) check(x + 1, y, x, y);
        if (y < 1001) check(x, y + 1, x, y);
        if (cmap[x][y] == 4) c++;
        rout << c << endl;
    }
    return 0;
}