/*
ID: william234
TASK: test
LANG: C++
*/
#define PROGRAM_NAME "test"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define DEBUG 0
#define USE_FILE 0
#if USE_FILE
#define rin fin
#define rout fout
#define MAIN_FILE_HEADER                \
    ofstream fout(PROGRAM_NAME ".out"); \
    ifstream fin(PROGRAM_NAME ".in");
#else
#define rin cin
#define rout cout
#define MAIN_FILE_HEADER
#endif
#if DEBUG
#define IFDEBUG(stmt) stmt;
#define DBGOUT(stmt) cout << stmt;
#else
#define IFDEBUG(stmt)
#define DBGOUT(stmt)
#endif

int cows[20], maxHeights[20];
long long res = 1;

using namespace std;

int main() {
    MAIN_FILE_HEADER
    int n;
    rin >> n;
    for (int i = 0; i < n; i++) {
        rin >> cows[i];
    }
    for (int i = 0; i < n; i++) {
        rin >> maxHeights[i];
    }
    sort(maxHeights, maxHeights + n, greater<int>());
    sort(cows, cows + n, greater<int>());
    for (int i = 0; i < n; i++) {
        DBGOUT(cows[i] << ", " << maxHeights[i] << endl)
    }
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = i; j < n; j++) {
            if (cows[i] > maxHeights[j]) {
                break;
            }
            DBGOUT (": " << cows[i] << " to " << maxHeights[j] << endl)
            count ++;
        }
        DBGOUT(count << endl;)
        maxHeights[i] = 0;
        res *= count;
    }
    rout << res << endl;
    return 0;
}