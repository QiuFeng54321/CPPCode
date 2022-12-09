#include <iostream>
#include <iomanip>
using namespace std;
int main() {
    int n, f = 1;
    float s = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        s += 1.0 / f;
        f *= i;
    }
    cout << setprecision(10) << s << endl;
}