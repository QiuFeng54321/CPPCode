/*
ID: william234
TASK: ${ProgramName}
LANG: C++
*/
#define PROGRAM_NAME "${ProgramName}"
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
#pragma endregion
typedef pair<ll, ll> coords_t;
typedef map<ll, map<ll, pair<bool, int>>> pic_t;
pic_t pic;
pic_t oldPic;
set<coords_t> checkpoints;
set<coords_t> pointsToRemove, pointsToAdd;
ll minX, maxX, minY, maxY;

int dx[]{0, 1, 0, -1, 1, 1, -1, -1};
int dy[]{1, 0, -1, 0, 1, -1, 1, -1};

void activate(ll x, ll y) {
    dbgl("activate " << x << ", " << y);
    pic[x][y].ff = true;
    f0r(i, 8) {
        var nx = x + dx[i];
        var ny = y + dy[i];
        pic[nx][ny].ss++;
        if (!oldPic[nx][ny].ff && pic[nx][ny].ss == 3) {
            pointsToAdd.insert({nx, ny});
            dbgl("add " << nx << ", " << ny);
        }
    }
}
void deactivate(ll x, ll y) {
    dbgl("deactivate " << x << ", " << y);
    pic[x][y].ff = false;
    checkpoints.insert({x, y});
    f0r(i, 8) {
        var nx = x + dx[i];
        var ny = y + dy[i];
        pic[nx][ny].ss--;
        if (!oldPic[nx][ny].ff && pic[nx][ny].ss == 3) {
            pointsToAdd.insert({nx, ny});
            dbgl("add " << nx << ", " << ny);
        }
    }
}

void updateMinMax(ll x, ll y) {
    minX = min(minX, x);
    minY = min(minY, y);
    maxX = max(maxX, x);
    maxY = max(maxY, y);
}

void round_start() {
    oldPic = pic_t(pic);
    pointsToRemove.clear();
    if (checkpoints.empty()) {
        minX = minY = 1e18;
        maxX = maxY = -1e18;
    } else {
        minX = maxX = checkpoints.begin()->ff;
        minY = maxY = checkpoints.begin()->ss;
    }
}
void round_end() {
    for (car pi : pointsToRemove) {
        checkpoints.erase(pi);
    }
    for (car pi : pointsToAdd) {
        checkpoints.insert(pi);
    }
    pointsToAdd.clear();
}
void round() {
    round_start();
    for (car pi : checkpoints) {
        car[x, y] = pi;
        car[activated, neighbourCount] = oldPic[x][y];
        dbgl("Checking (" << x << ", " << y << "): " << activated << " with "
                          << neighbourCount << "neighbours");
        // Not activated and has no neighbour
        if (neighbourCount == 0 && !activated) {
            pointsToRemove.insert(pi);
            continue;
        }
        updateMinMax(x, y);
        if (activated && (neighbourCount > 3 || neighbourCount < 2)) {
            deactivate(x, y);
        }
        if (!activated && neighbourCount == 3) {
            activate(x, y);
        }
    }
    round_end();
}

void print_board(pic_t& picToPrint, ll off_x, ll off_y, ll w, ll h) {
    f0r(j, h) {
        f0r(i, w) {
            var x = off_x + i;
            var y = off_y + j;
            cout << (picToPrint[x][y].ff ? 'x' : ' ');
            dbg(picToPrint[x][y].ss);
            cout << ' ';
        }
        cout << '\n';
    }
    cout << "Viewing rect: from (" << off_x << ", " << off_y << ") to ("
         << (off_x + w) << ", " << (off_y + h) << ")" << endl;
}
// plane 0 0 0 1 0 2 1 0 2 1 -100
// stable 0 0 0 1 0 2 1 0 -100
// repeat 0 0 0 1 0 2 1 1 -100
// pulsar 0 0 1 0 2 0 2 1 1 2 0 -7 1 -7 0 -8 1 -8 4 -7 5 -7 4 -8 5 -8 -100
const ll stoppingNumber = -100;

void test() {
    round_start();
    while (true) {
        ll x, y;
        cin >> x;
        if (x == stoppingNumber) break;
        cin >> y;
        if (y == stoppingNumber) break;
        activate(x, y);
        pointsToAdd.insert({x, y});
        updateMinMax(x, y);
    }
    round_end();
    dbgl(minX << ", " << minY << ", " << maxX << ", " << maxY) print_board(
        pic, minX - 3, minY - 3, (maxX - minX + 6), (maxY - minY + 6));
    int roundNumber = 1;
    while (true) {
        str in;
        getline(std::cin, in);
        if (in == "q") break;
        round();
        print_board(pic, minX - 3, minY - 3, (maxX - minX + 6),
                    (maxY - minY + 6));
        cout << "Round " << roundNumber++ << endl;
    }
}

int main() {
    MAIN_FILE_HEADER
    test();
    return 0;
}