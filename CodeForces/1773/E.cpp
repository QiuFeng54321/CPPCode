/*
ID: william234
TASK: E
LANG: C++
*/
#define PROGRAM_NAME "E"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <iomanip>

#pragma region States
#define DEBUG 1
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
#define f0r(i, n) for(int i = 0; i < n; i++)
#define f0ri(i, n) for(int i = 0; i <= n; i++)
#define f1r(i, n) for(int i = 1; i < n; i++)
#define f1ri(i, n) for(int i = 1; i <= n; i++)
using namespace std;
using str = string;
using ll = long long;
template<typename T>
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
template<typename T>
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
#pragma endregion

const int N = 10002;

int n, cnt;
ll nums[N];
int k[N];
int idx[N];
bool isTop[N];
int tower[N];
int sortedH[N];
vector<int> towers[N];
vector<int> sortedSegs[N];
int split, combination;

bool cmp(int a, int b) {return nums[a] > nums[b];}

void moveT(int from, int to, int amount) {
    if (amount == 0) return;
    if (!towers[to].empty()) {
        isTop[towers[to].back()] = false;
        combination ++;
    }
    stack<int> tmp;
    f0r(_, amount) {
        tmp.push(towers[from].back());
        towers[from].pop_back();
    }
    if (!towers[from].empty()) {
        isTop[towers[from].back()] = true;
    }
    while (!tmp.empty()) {
        towers[to].push_back(tmp.top());
        tower[tmp.top()] = to;
        tmp.pop();
    }
}

void solve() {
}

int main() {
    MAIN_FILE_HEADER
    cin >> n;
    int flatIdx = 0;
    f0r(i, n) {
        cin >> k[i];
        cnt += k[i];
        f0r(j, k[i]) {
            cin >> nums[flatIdx];
            idx[flatIdx] = flatIdx;
            flatIdx++;
        }
    }
    sort(idx, idx + cnt, cmp); // Compression
    flatIdx = 0;
    f0r(i, n) {
        dbg("Tower " << i << ": ");
        f0r(j, k[i]) {
            dbg(idx[flatIdx] << ' ');
            int numIdx = idx[flatIdx];
            if (!towers[i].empty()) {
                isTop[towers[i].back()] = false;
                if (numIdx + 1 == towers[i].back()) {
                    sortedH[i] = towers[i].size();
                    sortedSegs[i].back()++;
                } else {
                    sortedSegs[i].push_back(1);
                }
            }
            towers[i].push_back(numIdx);
            isTop[numIdx] = true;
            tower[numIdx] = i;
            flatIdx++;
        }
        dbg(endl);
    }
    dbgs f0r(i, n) {
        dbgl("SortedH[" << i << "] = " << sortedH[i]);
    }
    f0r(i, cnt) {

    }
    return 0;
}