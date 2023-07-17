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
bool visited[52];

set<int> parents[52];
bool dependent[52];

int ord(char c) {
    if ('a' <= c && c <= 'z') return c - 'a';
    return c - 'A';
}

void solve() {
    memset(graph, -1, sizeof(graph));
    memset(visited, 0, sizeof(visited));
    memset(dependent, 0, sizeof(dependent));
    for (int i = 0; i < 52; i++) {
        parents[i].clear();
    }
    cin >> a >> b;
    n = a.size();
    set<int> uniqueChar{};
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
        if (visited[i]) continue;
        

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