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

int freq[52];

int main() {
    MAIN_FILE_HEADER
    int n;
    cin >> n;
    ll sum = 0;
    f0r(_, n / 3) {
        str strs[3];
        cin >> strs[0] >> strs[1] >> strs[2];
        memset(freq, 0, 52 * sizeof(int));
        f0r(i, 3) {
            str cur = strs[i];
            for (char ch : cur) {
                int ind = ch;
                ind -= ind <= 'Z' ? 'A' - 26 : 'a';
                if ((freq[ind] & (1 << i)) == 0) freq[ind] |= 1 << i;
                // cout << ch;
            }
        }
        f0r(i, 52) {
            // cout << freq[i] << ' ';
            if (freq[i] == 7) {
                cout << (char)(i >= 26 ? (i - 26 + 'A') : (i + 'a')) << ' '; 
                sum += i + 1;
            } 
        }
        cout << endl;
    }
    cout << sum << endl;
    return 0;
}