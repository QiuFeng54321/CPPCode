/*
ID: william234
TASK: ${ProgramName}
LANG: C++
*/
#define PROGRAM_NAME "${ProgramName}"
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
map<ll, int> m;

int main() {
    MAIN_FILE_HEADER
    ll n, a, c = 0;
    ll sum = 0;
    m[0] = 1;
    rin >> n;
    for (int i = 0; i < n; i++) {
        rin >> a;
        sum = (sum + a) % n;
        if (sum < 0) sum = n + sum;
        DBGOUT(sum << endl)
        c += m[sum];
        m[sum] ++;
    }
    rout << c << endl;
    return 0;
}