/*
ID: william234
TASK: paintbarn
LANG: C++                 
*/
#include <iostream>
#include <fstream>
#include <string>


#define DEBUG 1
#define USE_FILE 1
#define PROGRAM_NAME "paintbarn"
#define rin (USE_FILE ? fin : cin)
#define rout (USE_FILE ? fout : cout)
#define IFDEBUG(stmt) if (DEBUG) {stmt;}
#define DBGOUT if(DEBUG) cout
#define MAIN_FILE_HEADER \
    ofstream fout (PROGRAM_NAME ".out");\
    ifstream fin (PROGRAM_NAME ".in");

using namespace std;
int map[1001][1001];

int main() {
#if USE_FILE
    MAIN_FILE_HEADER
#endif
    int n, k;
    rin >> n >> k;
    for (auto x = 0; x < n; x ++) {
        int x1, y1, x2, y2;
        rin >> x1 >> y1 >> x2 >> y2;
        map[x1][y1] ++;
        map[x1][y2] --;
        map[x2][y1] --;
        map[x2][y2] ++;
    }
    int result = 0;
    for (int x = 0; x < 1000; x++) {
        for (int y = 0; y < 1000; y++) {
            if (x) map[x][y] += map[x - 1][y];
            if (y) map[x][y] += map[x][y - 1];
            if (x && y) map[x][y] -= map[x - 1][y - 1];
            if (map[x][y] == k) result ++;
        }
    }
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 20; y++) {
            DBGOUT << map[x][y];
        }
        DBGOUT << endl;
    }

    rout << result << endl;

    return 0;
}