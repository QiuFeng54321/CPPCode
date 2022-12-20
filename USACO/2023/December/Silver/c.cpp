#define PROGRAM_NAME "c"
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
using namespace std;

const int N = 100000;
int n;
int a[N];

bool isPrime(int n) {
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}
bool step(int i) {
    if (a[i] == 1) return true;
    if (isPrime(a[i])) return true;
    for (int x = a[i]; x > 1; x--) {
        if (a[i] - x > 1 && !isPrime(a[i] - x)) {
            a[i] -= x;
            // cout << "a" << i << " -= " << x << endl;
            return false;
        }
    }
    a[i]--;
    // cout << "a--\n";
    return false;
}

bool solve() {
    for (int i = 0; i < n; i = (i + 1) % n) {
        if (step(i)) return true;
        if (step(i)) return false;
    }
}
int t;
int main() {
    // freopen(PROGRAM_NAME ".in", "r", stdin);
    // freopen(PROGRAM_NAME ".out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        for (int j = 0; j < n; j++) {
            cin >> a[j];
        }
        bool res = solve();
        cout << (res ? "Farmer John" : "Farmer Nhoj") << endl;
    }
    return 0;
}