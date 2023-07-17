/*
ID: william234
TASK: E
LANG: C++
*/
#define PROGRAM_NAME "E"
#include <algorithm>
#include <bitset>
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
#pragma endregion

struct Segment {
    int l, r;
};

const int N = 1e5;
int vertex[4 * N];  // No. ones
bitset<N> arr;
int t, n, m, q;
Segment segments[N];
multiset<int> action_hist;
int actions[N];

void print_arr() {
    f0r(i, n) { cout << arr[i]; }
}

void set_bit(int v, int i, bool val, int l, int r) {
    if (l == r) {
        vertex[v] = val;
        arr[i] = val;
    } else {
        auto mid = (l + r) / 2;
        if (i <= mid) set_bit(v * 2, i, val, l, mid);
        else set_bit(v * 2 + 1, i, val, mid + 1, r);
        vertex[v] = vertex[v * 2] + vertex[v * 2 + 1];
    }
}

void set_bit(int i, bool val) { set_bit(1, i, val, 0, n - 1); }
void perform(int l, int r, bool undo) {
    for (int i = l; i <= r; i++) {
        if (undo) {
            action_hist.extract(actions[i]);
            if (action_hist.find(actions[i]) == action_hist.end()) {
                dbgs cout << "Set " << actions[i] << endl;
                set_bit(actions[i], false);
            }
        } else {
            if (action_hist.find(actions[i]) == action_hist.end()) {
                dbgs cout << "Unset " << actions[i] << endl;
                set_bit(actions[i], true);
            }
            action_hist.insert(actions[i]);
        }
    }
}
int seg_ones(int v, int vl, int vr, int l, int r) {
    // dbgs cout << "SegTree " << vl << " .. " << vr << " for " << l << " .. "
    // << r << endl;
    if (l == vl && r == vr) {
        return vertex[v];
    }
    int mid = (vl + vr) / 2;
    if (r <= mid) return seg_ones(v * 2, vl, mid, l, r);
    if (l > mid) return seg_ones(v * 2 + 1, mid + 1, vr, l, r);
    return seg_ones(v * 2, vl, mid, l, mid) +
           seg_ones(v * 2 + 1, mid + 1, vr, mid + 1, r);
}

bool any_valid() {
    f0r(i, m) {
        const auto& seg = segments[i];
        auto ones = seg_ones(1, 0, n - 1, seg.l, seg.r);
        dbgs cout << "[" << seg.l << " .. " << seg.r << "] has " << ones
                  << " ones" << endl;
        if (ones > ((seg.r - seg.l + 1) / 2)) return true;
    }
    return false;
}
int find_ans() {
    int hi = q;
    int lo = 0;
    int prev_mid = -1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (prev_mid < mid) {
            perform(prev_mid + 1, mid, false);
        }
        if (prev_mid > mid) {
            perform(mid + 1, prev_mid, true);
        }

        dbgs {
            cout << "[" << lo << ".." << hi << "], " << mid << ": ";
            print_arr();
            cout << endl;
        }
        prev_mid = mid;
        if (any_valid()) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}

void solve() {
    cin >> n >> m;
    memset(vertex, 0, sizeof(vertex));
    arr.reset();
    action_hist.clear();
    f0r(i, m) {
        cin >> segments[i].l >> segments[i].r;
        segments[i].l--;
        segments[i].r--;
    }
    cin >> q;
    f0r(i, q) {
        cin >> actions[i];
        actions[i]--;
    }
    int ans = find_ans();
    cout << (ans == q ? -1 : (ans + 1)) << endl;
}

int main() {
    MAIN_FILE_HEADER
    cin >> t;
    f0r(i, t) { solve(); }
    return 0;
}