/*
ID: william234
TASK: pairup
LANG: C++
*/
// Records {count, output} and sort them.
// Two-pointers: one at lowest and one at highest.
// Subtract the shared count that both have (min(output[l].count, output[r].count))
// Update maximum output
#define PROGRAM_NAME "pairup"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define DEBUG 0
#define USE_FILE 1
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

struct Output {
    int output;
    int count;
};
Output outputs[100000];
bool cmp(const Output& x, const Output& y) { return x.output < y.output; }

int main() {
    MAIN_FILE_HEADER
    int n;
    rin >> n;
    for (int i = 0; i < n; i++) {
        rin >> outputs[i].count >> outputs[i].output;
    }
    sort(outputs, outputs + n, cmp);
    int l = 0, r = n - 1;
    int maxTime = 0;
    while (r > l) {
        int time = outputs[r].output + outputs[l].output;
        maxTime = max(time, maxTime);
        auto maxCount = min(outputs[l].count, outputs[r].count);
        outputs[l].count -= maxCount;
        outputs[r].count -= maxCount;
        if (outputs[l].count == 0) l++;
        if (outputs[r].count == 0) r--;
        DBGOUT(l << " " << r << " " << time << endl)
    }
    rout << maxTime << endl;
    return 0;
}