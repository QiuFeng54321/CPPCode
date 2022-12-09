/*
ID: william234
TASK: berries
LANG: C++
*/
#define PROGRAM_NAME "berries"
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

using namespace std;

int main() {
    MAIN_FILE_HEADER
    return 0;
}