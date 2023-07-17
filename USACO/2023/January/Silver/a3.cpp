#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <memory>
#include <set>
#include <string>

using namespace std;

int t, n;
string a, b;
int graph[52];
bool replaced[52];
bool visWOLoop[52];
bool loopVis[52];
#define DEBUG 0
#define dbgs if (DEBUG)

int ord(char c) {
    if ('a' <= c && c <= 'z') return c - 'a';
    return c - 'A' + 26;
}

void solve() {
    memset(graph, -1, sizeof(graph));
    memset(replaced, 0, sizeof(replaced));
    memset(visWOLoop, 0, sizeof(replaced));
    memset(loopVis, 0, sizeof(replaced));
    cin >> a >> b;
    n = a.size();
    int ans = 0;
    set<int> uniqueChar{};
    uniqueChar.clear();
    for (int i = 0; i < n; i++) {
        auto c = ord(a[i]);
        auto d = ord(b[i]);
        uniqueChar.insert(c);
        if (graph[c] != -1 && graph[c] != d) {
            cout << -1 << endl;
            return;
        }
        graph[c] = d;
    }
    uint64_t a1ns = 0x0;
    uint64_t a2ns = 0x0;
    for (size_t i = 0; i < n; i++)
    {
        a1ns = a1ns | (0x1ll << ord(a[i]));
        a2ns = a2ns | (0x1ll << ord(b[i]));
    }
    uint64_t common = a1ns & a2ns;
    uint64_t unique1 = a1ns & (~common);
    uint64_t unique2 = a2ns & (~common);
    size_t unique1Size = 0;
    size_t unique2Size = 0;
    for (uint64_t mask = 0x8000; mask != 0x0; mask >>= 1)
    {
        unique1Size = (mask & unique1) != 0 ? unique1Size + 1 : unique1Size;
        unique2Size = (mask & unique2) != 0 ? unique2Size + 1 : unique2Size;
    }

    std::cout << "u1sz = " << unique1Size << std::endl
        << "u2sz = " << unique2Size << std::endl;
    cout << ans << endl;
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}