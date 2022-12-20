#define PROGRAM_NAME "a"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <vector>
#include <set>

using namespace std;
using ll = long long;
#define DEBUG 0

const int N = 200000;
int n;
ll h[N];
int idx[N];
vector<int> paths[N];
set<pair<ll, int>> heights;
vector<tuple<int, int, ll>> res;
ll sum, each;
ll costs[N];

bool cmp(int a, int b) { return costs[a] > costs[b]; }

void solve(int c, int par) {
    for (int i : paths[c]) {
        if (i == par) continue;
        if (costs[i] > 0) {
            solve(i, c);
            res.push_back({i, c, costs[i]});
            costs[c] += costs[i];
            costs[i] = 0;
        } else if (costs[i] < 0) {
            ll take = -costs[i];
            costs[i] = 0;
            costs[c] -= take;
            res.push_back({c, i, take});
            solve(i, c);
        }
    }
}

ll cost(int i, int par) {
    ll c = h[i] - each;
    for (const auto& e : paths[i]) {
        if (e == par) continue;
        c += cost(e, i);
    }
    costs[i] = c;
    return c;
}

int main() {
    // freopen(PROGRAM_NAME ".in", "r", stdin);
    // freopen(PROGRAM_NAME ".out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;

    int hiI = 0;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        sum += h[i];
        if (h[i] > h[hiI]) hiI = i;
        heights.insert({h[i], i});
    }
    each = sum / n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        paths[a].push_back(b);
        paths[b].push_back(a);
    }
    cost(hiI, -1);
    for (int i = 0; i < n; i++) {
        sort(paths[i].begin(), paths[i].end(), cmp);
    }
    solve(hiI, -1);
    cout << res.size() << endl;
    for (const auto& t : res) {
        cout << get<0>(t) + 1 << ' ' << get<1>(t) + 1 << ' ' << get<2>(t) << endl;
    }
    return 0;
}