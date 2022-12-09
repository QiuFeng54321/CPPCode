/*
ID: william234
TASK: multimoo
LANG: C++
*/
#define PROGRAM_NAME "multimoo"
#include <algorithm>
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
#define USE_FILE 1
#define PARALLEL 1
#define MOD 1000000007
#define USE_DSU 0
#pragma endregion

#pragma region Definitions
#if defined(__GNUC__) && !defined(__clang__)
#if PARALLEL
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#endif
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
#define f first
#define s second
#define F0R(i, n) for (int i = 0; i < n; i++)
#define F0Ri(i, n) for (int i = 0; i <= n; i++)
#define F1R(i, n) for (int i = 1; i < n; i++)
#define F1Ri(i, n) for (int i = 1; i <= n; i++)
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
#pragma endregion

const int N = 250;
int n;
int pic[N][N];
bool visited[N][N];
int dx[]{0, 1, 0, -1};
int dy[]{1, 0, -1, 0};

int hsh(int x, int y) { return x * N + y; };
map<int, int> areas;
map<int, int> to_origin;
map<pair<int, int>, int> dareas;
map<pair<int, int>, set<int>> visitedPairs;
int maxArea;
int maxArea2;

void solve(int ox, int oy, int x, int y) {
    visited[x][y] = true;
    to_origin[hsh(x, y)] = hsh(ox, oy);
    areas[hsh(ox, oy)]++;
    dbgl("Area at " << x << ", " << y << "( " << hsh(ox, oy) << ") col "
                    << pic[x][y] << " -> " << areas[hsh(ox, oy)]);
    F0R(di, 4) {
        int nx = x + dx[di];
        int ny = y + dy[di];
        if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
        if (!visited[nx][ny] && pic[nx][ny] == pic[x][y]) solve(ox, oy, nx, ny);
    }
}
void solve2(int x, int y) {
    visited[x][y] = true;
    auto origin = to_origin[hsh(x, y)];
    maxArea = max(maxArea, areas[origin]);
    F0R(di, 4) {
        int nx = x + dx[di];
        int ny = y + dy[di];
        if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
        auto norigin = to_origin[hsh(nx, ny)];
        pair<int, int> key = {min(pic[x][y], pic[nx][ny]),
                              max(pic[x][y], pic[nx][ny])};
        pair<int, int> pairKey = {min(origin, norigin), max(origin, norigin)};
        if (pic[x][y] != pic[nx][ny]) {
            if (!visitedPairs[key].count(origin)) {
                visitedPairs[key].insert(origin);
                dareas[key] += areas[origin];
            }
            if (!visitedPairs[key].count(norigin)) {
                visitedPairs[key].insert(norigin);
                dareas[key] += areas[norigin];
            }
        }
    }
    F0R(di, 4) {
        int nx = x + dx[di];
        int ny = y + dy[di];
        if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
        if (visited[nx][ny]) continue;
        solve2(nx, ny);
    }
}

int main() {
    MAIN_FILE_HEADER
    cin >> n;
    F0R(i, n) {
        F0R(j, n) { cin >> pic[i][j]; }
    }
    F0R(i, n) {
        F0R(j, n) {
            if (visited[i][j]) continue;
            solve(i, j, i, j);
        }
    }
    memset(visited, 0, N * N);
    solve2(0, 0);
    for (const auto& [p, a] : dareas) {
        dbgl(p.f << " to " << p.s << ": " << a);
        maxArea2 = max(maxArea2, a);
    }

    dbgs F0R(i, n) {
        F0R(j, n) { dbg(areas[to_origin[hsh(i, j)]] << ' '); }
        dbg('\n');
    }
    dbgs F0R(i, n) {
        F0R(j, n) { dbg(pic[i][j] << ' '); }
        dbg('\n');
    }

    cout << maxArea << "\n" << maxArea2 << endl;
    return 0;
}