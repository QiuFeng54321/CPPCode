/*
ID: william234
TASK: MovieFestivalII
LANG: C++
*/
#define PROGRAM_NAME "MovieFestivalII"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
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
#if USE_FILE
#define MAIN_FILE_HEADER                     \
    freopen(PROGRAM_NAME ".in", "r", stdin); \
    freopen(PROGRAM_NAME ".out", "w", stdout);
#else
#define MAIN_FILE_HEADER         \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);
#endif
#if DEBUG
#define IFDEBUG(stmt) stmt;
#define DBGOUT(stmt) cout << stmt;
#else
#define IFDEBUG(stmt)
#define DBGOUT(stmt)
#endif
#define ll long long
#pragma endregion

using namespace std;

struct movie {
    ll start, end;
    bool operator<(const movie& b) const { return end < b.end; }
};
multiset<movie, less<movie>> movies;
int n, k;
int c;
multiset<int, less<int>> people;

int main() {
    MAIN_FILE_HEADER
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        movie m{};
        cin >> m.start >> m.end;
        movies.insert(m);
    }
    for (int i = 0; i < k; i++) {
        people.insert(0);
    }
    while (movies.size() > 0) {
        auto m = movies.begin();
        DBGOUT(m->start << "->" << m->end << "\n")
        auto lb = people.upper_bound(m->start);
        if (lb != people.begin()) {
            lb--;
            DBGOUT(*lb)
            people.erase(lb);
            people.insert(m->end);
            c++;
            DBGOUT(" to " << m->end << "\n")
        }
        movies.erase(m);
    }
    cout << c << endl;
    return 0;
}