#define PROGRAM_NAME "teleport"
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

const int N = 100000;
int n;

map<int, int> changes;

void solve() {
    cin >> n;
    ll current_cost = 0;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        current_cost += abs(a - b);
        if (abs(a) > abs(a - b)) continue;
        changes[b] += 2;
        if (a < 0 && b > a) {changes[0]--; changes[2 * b]--;}
        if (a >= 0 && b <= a) {changes[0]--; changes[2 * b]--;}
        if (a >= 0 && b > a) {changes[2 * a]--; changes[2 * b - 2 * a]--;}
        if (a < 0 && b <= a) {changes[2 * a]--; changes[2 * b - 2 * a]--;}
    }
    ll min_cost = current_cost, last_y = -1e8;
    ll slope = 0;
    for (auto& [y, d_slope] : changes) {
        current_cost += (y - last_y) * slope;
        last_y = y;
        slope += d_slope;
        min_cost = min(min_cost, current_cost);
    }
    cout << min_cost << endl;
}

int main() {
    freopen(PROGRAM_NAME ".in", "r", stdin);
    freopen(PROGRAM_NAME ".out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}