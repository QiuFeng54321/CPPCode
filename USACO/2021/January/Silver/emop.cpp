/*
ID: william234
TASK: test
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <string>

#define DEBUG 1
#define USE_FILE 0
#define PROGRAM_NAME "test"
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

using namespace std;

int o, e;
bool flag;
int r;
int main() {
    MAIN_FILE_HEADER
    int n;
    rin >> n;
    for (int i = 0; i < n; i++) {
        int num;
        rin >> num;
        if (num % 2 == 0)
            e++;
        else
            o++;
    }

    DBGOUT("E " << e << ", O " << o << ", R " << r << endl);
    while (o != 0 || e != 0) {
        flag = !flag;
        if (flag) {
            if (e) {
                e--;
                r++;
            } else {
                if (o >= 2) {
                    o -= 2;
                    r++;
                } else {
                    r--;
                    break;
                }
            }
        } else { // odd
            if (e) {
                if (o) {
                    e--;
                    o--;
                    r++;
                } else {
                    r--;
                    break;
                }
            } else {
                if (o) {
                    o--;
                    r++;
                } else {
                    r--;
                    break;
                }
            }
        }
        DBGOUT("E " << e << ", O " << o << ", R " << r << endl);
    }
    rout << r << endl;
    return 0;
}