/*
ID: william234
TASK: mtt
LANG: C++
*/
#define PROGRAM_NAME "mtt"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#pragma region States
#define DEBUG 0
#define USE_FILE 0
#define PARALLEL 1
#pragma endregion

#pragma region Definitions
#if PARALLEL
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
#define IFDEBUG(stmt) stmt;
#define DBGOUT(stmt) cout << stmt;
#else
#define IFDEBUG(stmt)
#define DBGOUT(stmt)
#endif
#define ll long long
using namespace std;
int last_true(int lo, int hi, function<bool(int)> f);
int first_true(int lo, int hi, function<bool(int)> f);
#pragma endregion

#define NO 0
#define M 2
#define O 3
#define SS 0
#define Sx 1
#define Sy 2
#define Sd 3

struct Instruction {
    bool hasInstruction;
    bool trespassable;
    int state;
    int x, y;
    bool visited;
};
Instruction maze[25][25];
int ttt[3][3];
int N;
const int MOO = M + O + O;
int dx[]{1, 0, -1, 0};
int dy[]{0, 1, 0, -1};
int ans = 0;
int bx, by;

void updateTTT(int x, int y, int inc) {
    ttt[x][y] = inc;
    bool valid = false;
    for (int i = 0; i < 3; i ++) {
        if (ttt[i][1] == O && ttt[i][0] == M && t)
    }
    if (valid) {
        ans++;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << ttt[i][j][SS];
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

void dfs(int x, int y) {
    for (int i = 0; i < 4; i++) {
        int cx = x + dx[i];
        int cy = y + dy[i];
        if (cx < 0 || cy < 0 || cx >= N || cy >= N) continue;
        auto& child = maze[cx][cy];
        if (child.visited || !child.trespassable) continue;
        cout << cx << ", " << cy << "\n";
        maze[cx][cy].visited = true;
        if (child.hasInstruction) {
            updateTTT(child.x, child.y, child.state);
        }
        dfs(cx, cy);
        cout << "<-";
        if (child.hasInstruction) {
            updateTTT(child.x, child.y, -child.state);
        }

        cout << "√\n";
    }
}

int main() {
    MAIN_FILE_HEADER
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char s, x, y;
            cin >> s >> x >> y;
            if (s == 'B') {
                bx = i;
                by = j;
                maze[i][j].visited = true;
            }
            if (s == '#') continue;
            if (s == '.') maze[i][j] = {false, true, 0, 0, 0};
            maze[i][j] = {true, true, s == 'M' ? M : O, x - '1', y - '1'};
        }
    }
    dfs(bx, by);
    cout << ans << endl;
    return 0;
}

#pragma region Functions
int last_true(int lo, int hi, function<bool(int)> f) {
    // if none of the values in the range work, return lo - 1
    lo--;
    while (lo < hi) {
        // find the middle of the current range (rounding up)
        int mid = lo + (hi - lo + 1) / 2;
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
int first_true(int lo, int hi, function<bool(int)> f) {
    hi++;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (f(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}
#pragma endregion