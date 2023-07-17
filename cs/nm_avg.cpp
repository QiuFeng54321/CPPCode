#define PROGRAM_NAME "nm_avg"
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

const int N = 200006;
int n, m;
vector<vector<ll>> res;
vector<ll> part_sum;
ll sum;
double avg;
int zeros;
set<ll> nums;

void solve() {}

void remove(set<ll>& s, set<ll>::iterator it, int j) {
    res[j].push_back(*it);
    part_sum[j] += *it;
    s.erase(it);
}
void remove(set<ll>& s, ll v, int j) {
    res[j].push_back(v);
    part_sum[j] += v;
    s.erase(v);
}

// 13 4 18 28 22 500 10 6 5 27 3 2 35 2 1
int main() {
    MAIN_FILE_HEADER
    cin >> n >> m;
    res.resize(m);
    part_sum.resize(m);
    f0r(i, n) {
        ll num;
        cin >> num;
        if (num == 0) {
            zeros++;
            continue;
        }
        sum += num;
        nums.insert(num);
    }
    n -= zeros;
    avg = sum / m;
    int startM = 0;
    while (startM < m - 1 && !nums.empty() && *nums.rbegin() > avg * 2) {
        dbgs cout << "rm " << *nums.rbegin() << " > " << avg * 2 << endl;
        sum -= *nums.rbegin();
        remove(nums, *nums.rbegin(), startM);
        startM ++;
        avg = sum / (m - startM);
        dbgs cout << "new sum = " << sum << ", new avg = " << avg << endl;;
    }
    cout << "avg = " << avg << endl;
    for (int j = startM; j < m; j++) {
        dbgs dbgs cout << "j = " << j << ": \n";
        ll currentDiff = (ll)avg;
        while (!nums.empty()) {
            auto lb = nums.lower_bound(currentDiff);
            auto rmVal = *nums.rbegin();
            if (lb != nums.end())  {
                if (*lb == currentDiff || lb == nums.begin()) {
                    rmVal = *lb;
                } else {
                    auto before = lb;
                    before--;
                    if (*lb - currentDiff > currentDiff - *before) {
                        rmVal = *before;
                    } else {
                        rmVal = *lb;
                    }
                }
            }
            dbgs cout << "add " << rmVal;
            if (j != m - 1 && currentDiff < abs(part_sum[j] + rmVal - avg)) {
                dbgs cout << "xxx \n";
                break;
            }
            remove(nums, rmVal, j);
            currentDiff = abs(avg - part_sum[j]);
            dbgs cout << "currentDiff = " << currentDiff << "\n";
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < res[i].size(); j++) {
            cout << res[i][j] << " ";
        }
        if (i == m - 1) {
            for (int j = 0; j < zeros; j++) {
                cout << "0 ";
            }
        }
        cout << "sum = " << part_sum[i];
        cout << endl;
    }
    // for (int i = 0; i < n; i++) {
    //     int minJ = 0;
    //     ll minDiff = part_sum[0] - arr[i];
    //     for (int j = 1; j < m; j++) {
    //         ll diff = abs(part_sum[j] - arr[i]);
    //         if (diff < minDiff) {
    //             minJ = j;
    //             minDiff = diff;
    //         }
    //     }

    // }
    return 0;
}