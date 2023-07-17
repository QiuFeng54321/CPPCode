/*
ID: william234
TASK: D
LANG: C++
*/
#define PROGRAM_NAME "D"
#include <algorithm>
#include <cmath>
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
#define MAIN_FILE_HEADER                       \
    freopen(PROGRAM_NAME ".in", "r", stdin);   \
    freopen(PROGRAM_NAME ".out", "w", stdout); \
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
#define ff first
#define ss second
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
template <typename T>
T last_true(T lo, T hi, function<bool(T)> f) {
    // if none of the values in the range work, return lo - 1
    lo--;
    while (lo < hi) {
        // find the middle of the current range (rounding up)
        T mid = lo + (hi - lo + 1) / 2;
        if (f(mid)) {
            // if mid works, then all numbers smaller than mid also work
            lo = mid;
        } else {
            // if mid does not work, greater values would not work either
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
// Int div a / b with negative result gives upper bound so this is the fix.
ll floorDiv(ll a, ll b) {
    ll val = a / b;
    while (val * b > a) val--;
    return val;
}
#if USE_DSU
struct DSU {
    vector<int> e;
    DSU(int N) { e = vector<int>(N, -1); }

    // get representive component (uses path compression)
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }

    bool same_set(int a, int b) { return get(a) == get(b); }

    int size(int x) { return -e[get(x)]; }

    bool unite(int x, int y) {  // union by size
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return true;
    }
};
#endif
// https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html
void sieve(vector<ll>& primes, vector<char>& is_prime, ll n) {
    ll nsqrt = sqrt(n);
    is_prime = vector<char>(nsqrt + 2, true);
    for (ll i = 2; i <= nsqrt; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = i * i; j <= nsqrt; j += i) is_prime[j] = false;
        }
    }
}

set<ll> unique_factors(ll n, vector<ll>& primes) {
    set<ll> factorization;
    for (ll d : primes) {
        if (d * d > n) break;
        while (n % d == 0) {
            factorization.insert(d);
            n /= d;
        }
    }
    if (n > 1) factorization.insert(n);
    return factorization;
}
// https://cp-algorithms.com/algebra/factorization.html#precomputed-primes
vector<ll> factorize(ll n, vector<ll>& primes) {
    vector<ll> factorization;
    for (ll d : primes) {
        if (d * d > n) break;
        while (n % d == 0) {
            factorization.push_back(d);
            n /= d;
        }
    }
    if (n > 1) factorization.push_back(n);
    return factorization;
}
#pragma endregion

const int N = 2e5;

void solve() {
    int n, cnt = 0;
    set<int> s{};
    cin >> n;
    int a[n];
    f0r(i, n) {
        int v;
        cin >> v;
        if (s.find(v) == s.end()) {
            s.insert(v);
            a[cnt] = v;
            cnt++;
        }
    }
    sort(a, a + cnt);

    auto seg = [&](int l, int r) {
        if (l > r) return pair{0, 0};
        if (l == r) return pair{0, a[l]};
        auto diff = a[r] - a[l];
        dbgs {
            cout << "Diff from " << l << " to " << r << ": " << diff << endl;
            for (int i = l; i <= r; i++) {
                cout << a[i] << " ";
            }
            cout << endl;
        }
        return pair{(diff >> 1) + (diff & 1), (a[r] + a[l]) / 2};
    };
    auto max_time = [&](int l, int r) {
        auto l_seg = seg(0, l), m_seg = seg(l + 1, r - 1),
             r_seg = seg(r, cnt - 1);
        return max(l_seg.first, max(m_seg.first, r_seg.first));
    };

    int l = 0, r = cnt - 1;
    auto ans = max_time(l, r);
    while (r - l > 1) {
        auto cur_max_l = max_time(l + 1, r);
        auto cur_max_r = max_time(l, r - 1);
        if (cur_max_l <= ans || cur_max_r <= ans) {
            if (ans - cur_max_l <= ans - cur_max_r) {
                l++;
                ans = cur_max_l;
            } else {
                r--;
                ans = cur_max_r;
            }
        } else
            break;
    }
    dbgs cout << "ans: " << a[l] << " " << a[r] << endl;
    cout << ans << endl;
}

int main() {
    MAIN_FILE_HEADER
    int t;
    cin >> t;
    f0r(i, t) solve();
    return 0;
}