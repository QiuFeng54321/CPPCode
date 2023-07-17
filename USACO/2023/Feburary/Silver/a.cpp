#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

#define DEBUG 1

#define dbgs if (DEBUG)
using namespace std;
using str = string;
using ll = long long;

template <typename T>
T last_true(T lo, T hi, function<bool(T)> f) {
    lo--;
    while (lo < hi) {
        T mid = lo + (hi - lo + 1) / 2;
        if (f(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    return lo;
}
template <typename T>
T first_true(T lo, T hi, function<bool(T)> f) {
    hi++;
    while (lo < hi) {
        T mid = lo + (hi - lo) / 2;
        if (f(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

ll tc, tm;
int t, n;
const int N = 100;
struct Req {
    ll a, b, c;
    ll need() { return a * tc + b * tm - c; }
};
Req reqs[N];
vector<Req> sceneA, sceneB;

bool cmp(Req& a, Req& b) { return a.need() > b.need(); }

ll money, minA, minB;

bool dcBinMin(ll dc) {
    for (auto& req : sceneA) {
        if (req.need() <= 0) continue;
        // if (req.a == req.b && (req.b * money) < req.need()) return false;
        if ((dc * (req.a - req.b) + req.b * money) < req.need()) return false;
    }
    return true;
}
bool dcBinMax(ll dc) {
    for (auto& req : sceneB) {
        if (req.need() <= 0) continue;
        if ((dc * (req.a - req.b) + req.b * money) < req.need()) return false;
    }
    return true;
}

bool moneyBin(ll m) {
    if (m > minA + minB) return false;
    money = m;
    ll lb = first_true<ll>(0, m, dcBinMin);
    ll ub = last_true<ll>(0, m, dcBinMax);
    if (lb > m || ub < 0) return false;
    dbgs if (lb <= ub) { cout << m << ": " << lb << ".." << ub << "\n"; }
    if (lb > ub) return false;
    for (ll i = lb; i <= ub; i++) {
        if (minA - i >= 0 && minB - (m - i) >= 0) return true;
    }
    return false;
}

void dbg(ll ans, ll v) {
    ll nc = tc - v;
    ll nm = tm - (ans - v);
    for (int i = 0; i < n; i++) {
        cout << i << ": " << reqs[i].a << " * " << nc << " + " << reqs[i].b
             << " * " << nm << " = " << (reqs[i].a * nc + reqs[i].b * nm)
             << " cmp " << reqs[i].c << endl;
    }
}

void solve() {
    sceneA.clear();
    sceneB.clear();
    minA = minB = 2e18;
    cin >> n >> tc >> tm;
    for (int i = 0; i < n; i++) {
        cin >> reqs[i].a >> reqs[i].b >> reqs[i].c;
        if (reqs[i].a >= reqs[i].b) {
            sceneA.push_back(reqs[i]);
        } else {
            sceneB.push_back(reqs[i]);
        }
        minA = min(minA, reqs[i].a);
        minB = min(minB, reqs[i].b);
    }
    sort(reqs, reqs + n, cmp);
    ll ans = first_true<ll>(0, 2e18, moneyBin);
    cout << ans << endl;
    dbgs {
        ll lb = first_true<ll>(0, ans, dcBinMin);
        ll ub = last_true<ll>(0, ans, dcBinMax);
        dbg(ans, lb);
        dbg(ans, ub);
    }
    dbgs cout << "\n------\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    dbgs {
        freopen("a.in", "r", stdin);
        freopen("a.out", "w", stdout);
    }
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}