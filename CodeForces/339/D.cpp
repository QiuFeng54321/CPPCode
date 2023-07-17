/*
ID: william234
TASK: D
LANG: C++
*/
#define PROGRAM_NAME "D"
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
#include <cmath>
#include <bitset>

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
#define f0r(i, n) for(int i = 0; i < n; i++)
#define f0ri(i, n) for(int i = 0; i <= n; i++)
#define f1r(i, n) for(int i = 1; i < n; i++)
#define f1ri(i, n) for(int i = 1; i <= n; i++)
using namespace std;
using str = string;
using ll = long long;
#pragma endregion

int n, m, cnt;
const int MAX_COUNT = 131072;
int a[MAX_COUNT];
int vertex[4 * MAX_COUNT];
bool is_top_or;

inline int merge(bool is_or, int x, int y) {
    return is_or ? (x | y) : (x ^ y);
}

void build(bool is_or, int v, int l, int r) {
    if (l == r) {
        vertex[v] = a[l];
    } else {
        int mid = (l + r) / 2;
        build(!is_or, v * 2, l, mid);
        build(!is_or, v * 2 + 1, mid + 1, r);
        vertex[v] = merge(is_or, vertex[v * 2], vertex[v * 2 + 1]);
    }
    dbgs cout << "Vertex[" << bitset<16>(v) << "] = " << vertex[v] << endl;
}

void update(bool is_or, int v, int i, int val, int l, int r) {
    if (l == r) {
        a[i] = vertex[v] = val;
    } else {
        int mid = (l + r) / 2;
        if (i <= mid) {
            update(!is_or, v * 2, i, val, l, mid);
        } else {
            update(!is_or, v * 2 + 1, i, val, mid + 1, r);
        }
        vertex[v] = merge(is_or, vertex[v * 2], vertex[v * 2 + 1]);
    }
}



void solve() {
    int p, b;
    cin >> p >> b;
    update(is_top_or, 1, p - 1, b, 0, cnt - 1);
    cout << vertex[1] << endl;
}

int main() {
    MAIN_FILE_HEADER
    cin >> n >> m;
    cnt = pow(2, n);
    is_top_or = n % 2;
    f0r(i, cnt) {
        cin >> a[i];
    }
    build(is_top_or, 1, 0, cnt - 1);
    f0r(i, m) {
        solve();
    }
    return 0;
}