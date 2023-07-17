#include <algorithm>
#include <cmath>
#include <iostream>

#define DEBUG 0

#define dbgs if (DEBUG)
using namespace std;
using str = string;
using ll = long long;

struct lt {
    ll x, y, t;
};

bool cmp(lt& a, lt& b) { return a.t < b.t; }
const int N = 100001;

lt grazing[N];
lt alibi[N];
bool canReachBack[N];
bool canReachForward[N];

int g, n;

bool canReach(lt& a, lt& b) {
    auto dx = a.x - b.x;
    auto dy = a.y - b.y;
    auto dt = b.t - a.t;
    return dx * dx + dy * dy <= dt * dt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("b.in", "r", stdin);
    // freopen("b.out", "w", stdout);
    cin >> g >> n;
    for (int i = 0; i < g; i++) {
        cin >> grazing[i].x >> grazing[i].y >> grazing[i].t;
    }
    for (int i = 0; i < n; i++) {
        cin >> alibi[i].x >> alibi[i].y >> alibi[i].t;
    }
    sort(grazing, grazing + g, cmp);
    sort(alibi, alibi + n, cmp);
    canReachBack[0] = true;
    canReachForward[g - 1] = true;
    for (int i = 1; i < g; i++) {
        canReachBack[i] =
            canReachBack[i - 1] && canReach(grazing[i], grazing[i - 1]);
        dbgs cout << (canReachBack[i] ? "C" : "N") << " ";
    }
    dbgs cout << endl;
    for (int i = g - 2; i >= 0; i--) {
        canReachForward[i] =
            canReachForward[i + 1] && canReach(grazing[i], grazing[i + 1]);
        dbgs cout << (canReachBack[i] ? "C" : "N") << " ";
    }
    dbgs cout << endl;
    int gi = 0;
    int notInnocent = 0;
    for (int i = 0; i < n; i++) {
        while (gi < g - 1 && grazing[gi].t < alibi[i].t) gi++;
        bool cr = canReach(grazing[gi], alibi[i]);
        bool canReachAll = false;
        if (gi == g - 1 && grazing[gi].t < alibi[i].t) {
            canReachAll = (cr && canReachBack[gi]);
        } else if (grazing[gi].t == alibi[i].t) {
            canReachAll = (cr && canReachBack[gi] && canReachForward[gi]);
        } else if (gi == 0) {
            canReachAll = (cr && canReachForward[gi]);
        } else {
            canReachAll = (cr && canReach(grazing[gi - 1], alibi[i]) &&
                     canReachBack[gi - 1] && canReachForward[gi]);
        }
        dbgs cout << (canReachAll ? "N" : "I");
        notInnocent += canReachAll;
    }
    dbgs cout << "\n";
    cout << n - notInnocent << endl;
    return 0;
}