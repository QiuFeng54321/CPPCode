/*
ID: william234
TASK: ${ProgramName}
LANG: C++
*/
#define PROGRAM_NAME "program"
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
#define MAIN_FILE_HEADER                     \
    freopen(PROGRAM_NAME ".in", "r", stdin); \
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

int dx[]{1, -1, 0, 0, 0, 0};
int dy[]{0, 0, 1, -1, 0, 0};
int dz[]{0, 0, 0, 0, 1, -1};
const int N = 100;
bool pic[N][N][N];
int component[N][N][N];
bool visSurf[N][N][N];
int n;
int surf;
int airCol = 1;
void color(int x, int y, int z, int compNum) {
    if (component[x][y][z]) return;
    component[x][y][z] = compNum;
    // dbgl(x << ", " << y << ", " << z)
    f0r(i, 6) {
        int ex = x + dx[i];
        int ey = y + dy[i];
        int ez = z + dz[i];
        if (ex < 0 || ey < 0 || ez < 0 || ex >= N || ey >= N || ez >= N)
            continue;
        if (pic[ex][ey][ez] == pic[x][y][z]) {
            color(ex, ey, ez, compNum);
        }
    }
}
void solve(int x, int y, int z) {
    if (!pic[x][y][z] || visSurf[x][y][z]) return;
    visSurf[x][y][z] = true;
    f0r(i, 6) {
        int ex = x + dx[i];
        int ey = y + dy[i];
        int ez = z + dz[i];
        if (ex < 0 || ey < 0 || ez < 0 || ex >= N || ey >= N || ez >= N){
            surf++;
            continue;
        }
        if (component[ex][ey][ez] == airCol)
            surf++;
        else if (pic[ex][ey][ez]) {
            solve(ex, ey, ez);
        }
    }
}

int main() {
    MAIN_FILE_HEADER
    cin >> n;
    f0r(i, n) {
        int x, y, z;
        cin >> x >> y >> z;
        pic[x][y][z] = true;
    }
    dbgl("Hi");
    int curComp = 1;
    f0r(x, N) {
        f0r(y, N) {
            f0r(z, N) {
                if (!component[x][y][z]) {
                    color(x, y, z, curComp++);
                }
            }
        }
    }
    dbgl("Colored")
    f0r(x, N) {
        f0r(y, N) {
            f0r(z, N) {
                if (pic[x][y][z] && !visSurf[x][y][z]) solve(x, y, z);
            }
        }
    }
    cout << surf << endl;
    return 0;
}