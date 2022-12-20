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

int n, m;
stack<char> crates[10];

void solve() {}

int main() {
    freopen(PROGRAM_NAME ".in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    fr(i, 0, n) {
        int x;
        cin >> x;
        fr(_, 0, x) {
            char type;
            cin >> type;
            crates[i].push(type);
        }
    }
    fr(_, 0, m) {
        int amount, from, to;
        cin >> amount >> from >> to;
        from--;
        to--;
        if (from == to) continue;
        stack<char> group;
        fr(__, 0, amount) {
            char popped = crates[from].top();
            crates[from].pop();
            group.push(popped);
        }
        while (!group.empty()) {
            char c = group.top(); group.pop();
            crates[to].push(c);
        }
    }
    fr(i, 0, n) { cout << crates[i].top(); }
    cout << endl;

    return 0;
}