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
#define DEBUG 1
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
    int ans = 0;
    for (int i = 0; i < 52; i++) {
        if (replaced[i]) continue;
        replaced[i] = true;
        if (graph[i] == i || graph[i] == -1) continue;
        int start = i, current = i;
        int len = 1;
        bool hasCycle = false;
        memset(loopVis, 0, sizeof(loopVis));
        loopVis[i] = true;
        while (graph[current] != -1) {
            if (graph[current] == current) break; // next is itself
            dbgs cout << current << " -> " << graph[current] << endl;
            current = graph[current]; // next
            len++;
            if (visWOLoop[current]) { // In contact with another graph
                dbgs cout << "collide\n";
                break;
            }
            if (loopVis[current]) { // Goes to a node already visited in this round
                hasCycle = true;
                break;
            }
            replaced[current] = loopVis[current] = true;
        }
        if (hasCycle && uniqueChar.size() >= 52) {
            cout << -1 << endl;
            return;
        }
        dbgs cout << (hasCycle ? "cycle" : "no cycle") << endl;
        if (hasCycle) {
            ans += len;
        } else {
            ans += len - 1;
        }
        memcpy(visWOLoop, replaced, sizeof(replaced));
    }
    cout << ans << endl;
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}