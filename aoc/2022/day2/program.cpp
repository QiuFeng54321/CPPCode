#define PROGRAM_NAME "program"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#pragma region States
#define DEBUG 1
#define USE_FILE 1
#define MOD 1000000007
#define USE_DSU 0
#pragma endregion

#pragma region Definitions
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#endif
#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);
#if USE_FILE
#define MAIN_FILE_HEADER                     \
    freopen(PROGRAM_NAME ".in", "r", stdin); \
    FAST_IO
#else
#define MAIN_FILE_HEADER FAST_IO
#endif
#if DEBUG
#define ifdbg(stmt) stmt;
#define dbg(stmt) cout << stmt;
#define dbgl(stmt) cout << stmt << endl;
#else
#define ifdbg(stmt)
#define dbg(stmt)
#define dbgl(stmt)
#endif
#define dbgs if (DEBUG)
#define f first
#define s second
#define car const auto&
#define ctr(t) const t&
#define var auto
#define all(x) x.begin(), x.end()
#define f0r(i, n) for (int i = 0; i < n; i++)
#define f0ri(i, n) for (int i = 0; i <= n; i++)
#define f1r(i, n) for (int i = 1; i < n; i++)
#define f1ri(i, n) for (int i = 1; i <= n; i++)
using namespace std;
using str = string;
using ll = long long;
#pragma endregion

ll score = 0;

int main() {
    MAIN_FILE_HEADER
    // "RPS"
    int n;
    cin >> n;
    f0r(i, n) {
        char oppCh, selfCh;
        cin >> oppCh >> selfCh;
        int opp = oppCh - 'A';
        int need = selfCh - 'X';
        int self = opp;
        if (need == 0) {
            self = (opp + 2) % 3;
        } else if (need == 1) {
            score += 3;
        } else {
            self = (opp + 1) % 3;
            score += 6;
        }
        score += self + 1;
    }
    cout << score << endl;
    return 0;
}