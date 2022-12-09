/*
ID: william234
TASK: mooyomooyo
LANG: C++
*/
#define PROGRAM_NAME "mooyomooyo"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
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

int N, K;
int board[10][100];
stack<pair<int, int>> path;
bool visited[10][100];
int lowest[10];
vector<vector<pair<int, int>>> blocks;
int xdir[]{0, 1, 0, -1};
int ydir[]{1, 0, -1, 0};

void print_board() {
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < 10; x++) {
            cout << board[x][y];
        }
        cout << "\n";
    }
}
// Gets all the blocks of numbers
void get_blocks() {
    blocks.clear();
    memset(visited, 0, 100 * 10);
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < N; y++) {
            if (visited[x][y] || board[x][y] == 0) continue;
            vector<pair<int, int>> block;
            block.push_back({x, y});
            path.push({x, y});
            int col = board[x][y];
            visited[x][y] = true;
            while (path.size() != 0) {
                auto pos = path.top();
                path.pop();
                for (int i = 0; i < 4; i++) {
                    int dx = pos.first + xdir[i];
                    int dy = pos.second + ydir[i];
                    if (dx < 0 || dx >= 10 || dy < 0 || dy >= N) continue;
                    if (visited[dx][dy] || board[dx][dy] != col) continue;
                    visited[dx][dy] = true;
                    block.push_back({dx, dy});
                    path.push({dx, dy});
                }
            }
            blocks.push_back(block);
        }
    }
}

// Eliminate blocks with size > K
bool eliminate() {
    bool any = false;
    for (const auto& block : blocks) {
        if (block.size() >= K) {
            any = true;
            for (auto& pos : block) {
                board[pos.first][pos.second] = 0;
                lowest[pos.first] = max(lowest[pos.first], pos.second);
            }
        }
    }

    // Fall down blocks
    for (int x = 0; x < 10; x++) {
        for (int y = N - 1; y >= 0; y--) {
            if (board[x][y] != 0 && y <= lowest[x]) {
                board[x][lowest[x]] = board[x][y];
                board[x][y] = 0;
                lowest[x]--;
            }
        }
    }
    return any;
}

int main() {
    MAIN_FILE_HEADER
    cin >> N >> K;
    memset(lowest, 0, 10);
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < 10; x++) {
            char c;
            cin >> c;
            board[x][y] = c - '0';
            if (c == '0') lowest[x] = max(lowest[x], y);
        }
    }
    while (true) {
        get_blocks();
        if (!eliminate()) break;
    }
    print_board();
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