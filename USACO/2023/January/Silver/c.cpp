#define PROGRAM_NAME "c"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>


using namespace std;
using ll = long long;

const int N = 1000005;
int a[N];
int n;

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] --;
        cout << 'R'; // Go to rightmost
    }
    int pos = n;
    int dir = -1;
    int rightMostHasValue = n - 1;
    while (rightMostHasValue != -1) {
        if (dir == 1) {
            if (pos > rightMostHasValue) {
                dir = -1;
            }
        }
        if (dir == -1) {
            if (pos == 0 || (a[pos + dir] == 1 && pos <= rightMostHasValue)) {
                dir = 1;
            }
        }
        int aidx = pos + (dir == -1 ? -1 : 0);
        a[aidx]--;

        // cout << endl << dir << ", " << pos << ": " << a[aidx] << endl;
        while (rightMostHasValue >= 0 && a[rightMostHasValue] == 0) rightMostHasValue--;
        pos += dir;
        cout << (dir == 1 ? "R" : "L");
    }
    cout << endl;
}

int main() {
    solve();
    return 0;
}