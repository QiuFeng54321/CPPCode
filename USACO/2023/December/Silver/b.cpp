#define PROGRAM_NAME "b"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>

using namespace std;
using ll = long long;

const int N = 300;
int n;
ll r[N][N];
ll dr[N][N];
pair<ll, ll> bounds[N];
ll b[N];
ll xmin[N][N], xmax[N][N];

int can(int i, ll x) {
    for (int j = 0; j <= i; j++) {
        ll nmax = j == i ? 0 : max(xmax[j][i - 1], x);
        ll nmin = j == i ? 0 : min(xmin[j][i - 1], x);
        cout << "b" << j << i << ", " << x << " = [" << nmin << ".." << nmax
             << "] expected " << r[j][i] << "\n";
        if (i == j || r[j][i] != r[j][i - 1]) {
            if (nmax - nmin < r[j][i]) {
                return x < xmin[j][i - 1] ? 1 : -1;
            }
            if (nmax - nmin > r[j][i]) {
                return x > xmax[j][i - 1] ? 1 : -1;
                // return 1;
            }
        }
        // if (nmax - nmin > r[j][i] && (i == j || r[j][i] != r[j][i-1])) return
        // 1;
    }
    return 0;
}

void solve() {
    for (int i = 1; i < n; i++) {
        ll hi = 1e9, lo = -1e9;
        while (lo < hi) {
            ll mid = lo + (hi - lo) / 2;
            int res = can(i, mid);
            if (res == 0) {
                b[i] = mid;
                for (int j = 0; j <= i; j++) {
                    xmin[j][i] = min(xmin[j][i - 1], b[i]);
                    xmax[j][i] = max(xmax[j][i - 1], b[i]);
                }
                xmin[i][i] = xmax[i][i] = b[i];
                cout << "Min\n";
                for (int j = 0; j < n; j++) {
                    for (int k = j; k < n; k++) {
                        cout << xmin[j][k] << " ";
                    }
                    cout << endl;
                }
                cout << "Max\n";
                for (int j = 0; j < n; j++) {
                    for (int k = j; k < n; k++) {
                        cout << xmax[j][k] << " ";
                    }
                    cout << endl;
                }
                break;
            }
            if (res == 1) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
    }
}

int main() {
    // freopen(PROGRAM_NAME ".in", "r", stdin);
    // freopen(PROGRAM_NAME ".out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            cin >> r[i][j];
            // xmin[i][j] = 2e9;
            // xmax[i][j] = -2e9;
            if (j - i > 0) {
                dr[i][j] = r[i][j] - r[i][j - 1];
            }
        }
    }
    b[0] = 0;
    xmin[0][0] = xmax[0][0] = 0;
    solve();
    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << b[i];
    }
    cout << endl;
    return 0;
}