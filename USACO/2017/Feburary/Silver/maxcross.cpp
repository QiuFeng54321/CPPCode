/*
ID: william234
TASK: maxcross
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define DEBUG 1
#define USE_FILE 1
#define PROGRAM_NAME "maxcross"
#define rin (USE_FILE ? fin : cin)
#define rout (USE_FILE ? fout : cout)
#define IFDEBUG(stmt)                                                                                                  \
    if (DEBUG)                                                                                                         \
    {                                                                                                                  \
        stmt;                                                                                                          \
    }
#define DBGOUT                                                                                                         \
    if (DEBUG)                                                                                                         \
    cout
#define MAIN_FILE_HEADER                                                                                               \
    ofstream fout(PROGRAM_NAME ".out");                                                                                \
    ifstream fin(PROGRAM_NAME ".in");

using namespace std;

vector<int> list;

int main()
{
#if USE_FILE
    MAIN_FILE_HEADER
#endif
    int n, k, b;
    rin >> n >> k >> b;
    list.resize(n);
    for (auto i = 0; i < b; i++)
    {
        int ind;
        rin >> ind;
        list[ind - 1] = 1;
    }
    for (auto i = 1; i < n; i++)
    {
        list[i] += list[i - 1];
        DBGOUT << list[i] << ", ";
    }
    DBGOUT << endl;
    int min = list[k - 1];
    DBGOUT << min << endl;
    for (auto i = k; i < n; i++)
    {
        int diff = list[i] - list[i - k];
        if (diff < min)
        {
            min = diff;
            DBGOUT << min << endl;
        }
    }
    rout << min << endl;
    return 0;
}