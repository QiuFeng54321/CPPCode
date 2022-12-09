/*
ID: william234
TASK: 1641
LANG: C++
*/
#define PROGRAM_NAME "1641"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define DEBUG 1
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

// a + b = x - c
ll nums[5000];
// key is x - c, value is all index with this value
map<ll, vector<int>> dc;


int main() {
    MAIN_FILE_HEADER
    int n, x;
    rin >> n >> x;
    for (auto i = 0; i < n; i++) {
        rin >> nums[i];
        auto diff = x - nums[i];
        if (dc.find(diff) == dc.end()) {
            dc[diff] = vector<int>{i};
        } else
            dc[diff].push_back(i);
    }
    int l = 0, r = n - 1;
    for (; l < n; l++) {
        for (r = l + 1; r < n; r++) {
            auto sum = nums[l] + nums[r];
            // No a + b = x - c found
            if (dc.find(sum) == dc.end()) {
                continue;
            }
            // If no duplicate index, output then exit
            for (auto index : dc[sum]) {
                if (index != l && index != r) {
                    rout << (l + 1) << " " << (r + 1) << " " << (index + 1) << endl;
                    return 0;
                }
            }
        }
    }
    rout << "IMPOSSIBLE" << endl;

    return 0;
}