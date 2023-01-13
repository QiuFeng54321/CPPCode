#define PROGRAM_NAME "lifeguards"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define DEBUG 0

#pragma region Definitions
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#endif
#define MOD 1000000007
#define dbgs if (DEBUG)
#define ff first
#define ss second
#define car const auto&
#define ctr(t) const t&
#define var auto
#define pb push_back
#define all(x) x.begin(), x.end()
#define fr(i, a, b) for (int i = a; i < b; i++)
#define fri(i, a, b) for (int i = a; i <= b; i++)
#define frr(i, a, b) for (int i = a; i >= b; i--)
using namespace std;
using str = string;
using ll = long long;
using pll = pair<ll, ll>;
using pi = pair<int, int>;
#pragma endregion

const int N = 100002;
int n;
ll removedLen[N];            // len
pair<ll, int> verts[2 * N];  // {x, seg_i}
pair<ll, ll> segs[N];        // {start, end}

void solve() {
    set<int> inSegs;                        // {seg_i}
    pair<ll, int> lastFinished = {-1, -1};  // {end_x, seg_i}
    ll totalLen = 0;
    ll lastX = 0;
    ll minLen = 1e18;
    for (int i = 0; i < 2 * n; i++) {
        dbgs cout << "{" << verts[i].ff << ", " << verts[i].ss << "}";
        if (inSegs.size() == 1) {  // Only one segment
            dbgs cout << "1";
            if (lastFinished.ss != -1) {
                dbgs cout << "f";
                removedLen[*inSegs.begin()] +=
                    min(verts[i].ff - segs[*inSegs.begin()].ff,
                        verts[i].ff - lastFinished.ff);
            } else {
                removedLen[*inSegs.begin()] +=
                    verts[i].ff - segs[*inSegs.begin()].ff;
            }
        }
        if (!inSegs.empty()) {
            totalLen += verts[i].ff - lastX;
        }
        if (inSegs.count(verts[i].ss)) {  // Segment end
            inSegs.erase(verts[i].ss);
            lastFinished = verts[i];
            minLen = min(minLen, removedLen[verts[i].ss]);
            dbgs cout << "- ";
        } else {  // Segment start
            inSegs.insert(verts[i].ss);
            dbgs cout << "+ ";
        }
        lastX = verts[i].ff;
    }
    cout << totalLen - minLen << "\n";
}

int main() {
    freopen(PROGRAM_NAME ".in", "r", stdin);
    freopen(PROGRAM_NAME ".out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    int j = 0;
    for (int i = 0; i < n; i++) {
        cin >> segs[i].first >> segs[i].second;
        verts[j].first = segs[i].first;
        verts[j + 1].first = segs[i].second;
        verts[j].second = verts[j + 1].second = i;
        j += 2;
    }
    sort(verts, verts + 2 * n);
    solve();
    return 0;
}