/*
ID: william234
TASK: E
LANG: C++
*/
#define PROGRAM_NAME "E"
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
#define DEBUG 0
#define USE_FILE 0
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

const int N = 400002;
// A flagged node indicates all bits below the node is LAZY_BIT
const auto LAZY_FLAG = 1 << 62;
const auto LAZY_BIT = 1 << 61;
const auto IS_LAZY_ON = LAZY_FLAG | LAZY_BIT;
const auto RESET_LAZY_MASK = ~IS_LAZY_ON;

ll a[N];
bitset<N> s;
// segtree[v] is xor(all s[i] where b[i] == 1)
ll segtree[4 * N];
ll pxor[N + 1];

ll range_xor(int l, int r) { return pxor[r + 1] ^ pxor[l]; }

void merge(int v) {
    int l = v * 2;
    int r = v * 2 + 1;
    ll res = (segtree[l] ^ segtree[r]) & RESET_LAZY_MASK;
    bool l_flag = segtree[l] & LAZY_FLAG != 0;
    bool r_flag = segtree[r] & LAZY_FLAG != 0;
    auto flag = !(l_flag ^ r_flag) ? LAZY_FLAG : 0;
    auto bit = segtree[l] & LAZY_BIT;
    segtree[v] = (segtree[l] ^ segtree[r]) & RESET_LAZY_MASK | flag | bit;
}

void build(int l, int r, int v) {
    if (l == r) {
        segtree[v] = (s[v] ? a[l] | LAZY_BIT : 0) | LAZY_FLAG;
    } else {
        int mid = (l + r) / 2;
        build(l, mid, v * 2);
        build(mid + 1, r, v * 2 + 1);
        merge(v);
    }
}

void update(int l, int r, int range_l, int range_r, int v, bool value) {
    if (l == r) {
        segtree[v] = (value ? a[l] | LAZY_BIT : 0) | LAZY_FLAG;
    } else if (l == range_l && r == range_r) {
        auto rxor = range_xor(l, r);
        segtree[v] = (value ? rxor | LAZY_BIT : 0) | LAZY_FLAG;
    } else {
        int mid = (l + r) / 2;
        if (range_l > mid) {
            update(mid + 1, r, range_l, range_r, v * 2, value);
        } else if (range_r <= mid) {
            update(l, mid, range_l, range_r, v * 2 + 1, value);
        } else {
            update(l, mid, range_l, mid, v * 2, value);
            update(mid + 1, r, mid + 1, range_r, v * 2 + 1, value);
        }
        merge(v);
    }
}

ll query(bool bit, int n) { return bit ? segtree[1] : range_xor(0, n); }

void solve() {
    int n;
    cin >> n;
    pxor[0] = 0;
    f0r(i, n) {
        cin >> a[i];
        pxor[i + 1] = pxor[i] ^ a[i];
    }
    string bit_str;
    cin >> bit_str;
    f0r(i, n) {
        s[i] = bit_str[i] == '1';
    }
    int q;
    cin >> q;
    f0r(i, q) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            
        }
    }
}

int main() {
    MAIN_FILE_HEADER
    return 0;
}