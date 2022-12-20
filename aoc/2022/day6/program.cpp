#define PROGRAM_NAME "program"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define DEBUG 0

#pragma region Definitions
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#endif
#define MOD 1000000007
#define dbgs if (DEBUG)
#define ff first
#define ss second
#define car const auto&
#define ctr(t) const t&
#define var auto
#define pb push_back
#define all(x) x.begin(), x.end()
#define fr(i, a, b) for (int i = a; i < b; i++)
#define fri(i, a, b) for (int i = a; i <= b; i++)
#define frr(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
using str = string;
using ll = long long;
using pll = pair<ll, ll>;
using pi = pair<int, int>;
#pragma endregion
int has[26];
int nodups;

int main() {
    freopen(PROGRAM_NAME ".in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    str s;
    cin >> s;
    const int uniqueN = 14;
    fr(i, 0, s.size()) {
        car c = s[i];
        if (i >= uniqueN) {
            has[s[i - uniqueN]]--;
            if (!has[s[i - uniqueN]]) nodups--;
        }
        has[c]++;
        if (has[c] == 1) {
            nodups++;
        }
        if (nodups == uniqueN) {
            cout << i + 1 << endl;
            break;
        }
    }

    return 0;
}