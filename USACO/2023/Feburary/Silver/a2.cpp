#include <algorithm>
#include <iostream>
#define DEBUG 0

#define dbgs if (DEBUG)
using namespace std;
using str = string;
using ll = long long;

struct f {
    int a;
    int b;
    ll c;
};
f fri[105];

bool cmp(f a1, f a2) { return a1.c < a2.c; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    dbgs {
        freopen("a.in", "r", stdin);
        freopen("a.out", "w", stdout);
    }
    ll t, n, tc, tm, moooney, uc, um, mooney;
    bool flag;
    cin >> t;
    for (int z = 0; z < t; z++) {
        cin >> n >> tc >> tm;
        for (int i = 0; i < n; i++) {
            cin >> fri[i].a >> fri[i].b >> fri[i].c;
        }
        // sort(fri,fri+N,cmp);
        mooney = tc + tm - 2;
        for (uc = 1; uc <= tc; uc++) {
            for (um = 1; um <= tm; um++) {
                flag = true;
                for (int i = 0; i < n; i++) {
                    if (uc * fri[i].a + um * fri[i].b > fri[i].c) {
                        flag = false;
                    }
                }
                if (flag == true && tc + tm - uc - um < mooney) {
                    mooney = tc + tm - uc - um;
                }
            }
        }
        cout << mooney << endl;
    }
}