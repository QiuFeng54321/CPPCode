/*
ID: william234
TASK: C
LANG: C++
*/
#define PROGRAM_NAME "C"
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
    int get(int x) { return e.at(x) < 0 ? x : e.at(x) = get(e.at(x)); }

    bool same_set(int a, int b) { return get(a) == get(b); }

    int size(int x) { return -e.at(get(x)); }

    bool unite(int x, int y) {  // union by size
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e.at(x) > e.at(y)) swap(x, y);
        e.at(x) += e.at(y);
        e.at(y) = x;
        return true;
    }
};
#endif
void sieve(vector<ll>& primes, vector<char>& is_prime, ll n) {
    ll nsqrt = sqrtl(n);
    is_prime = vector<char>(nsqrt + 2, true);
    for (ll i = 2; i <= nsqrt; i++) {
        if (is_prime.at(i)) {
            primes.push_back(i);
            for (ll j = i * i; j <= nsqrt; j += i) is_prime.at(j) = false;
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

int n, t;
vector<ll> primes;
vector<char> is_prime;
map<ll, int> primeFreq;

void solve() {
    primeFreq.clear();
    cin >> n;
    f0r(i, n) {
        ll x;
        cin >> x;
        var factors = unique_factors(x, primes);
        for (car factor : factors) {
            primeFreq[factor]++;
        }
    }
    bool success = false;
    for (car[x, f] : primeFreq) {
        dbgl(x << ": " << f) if (f > 1) {
            cout << "YES" << endl;
            success = true;
            break;
        }
    }
    if (!success) cout << "NO" << endl;
}

int main() {
    MAIN_FILE_HEADER
    sieve(primes, is_prime, 1e9);
    cin >> t;
    f0r(_, t) { solve(); }
    return 0;
}