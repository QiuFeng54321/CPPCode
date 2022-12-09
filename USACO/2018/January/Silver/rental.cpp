/*
ID: william234
TASK: rental
LANG: C++
*/
#define PROGRAM_NAME "rental"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <assert.h>
#include <vector>

#pragma region States
#define DEBUG 0
#define USE_FILE 1
#define PARALLEL 1
#define MOD 1000000007
#pragma endregion

#pragma region Definitions
#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);
#if USE_FILE
#define MAIN_FILE_HEADER                       \
    freopen(PROGRAM_NAME ".in", "r", stdin);   \
    freopen(PROGRAM_NAME ".out", "w", stdout); \
    FAST_IO
#else
#define MAIN_FILE_HEADER FAST_IO
#endif
#if DEBUG
#define ifdbg(stmt) stmt;
#define dbg(stmt) cout << stmt;
#define dbgl(stmt) cout << stmt << endl;
#else
#define ifdbg(stmt)
#define dbg(stmt)
#define dbgl(stmt)
#endif
#define dbgs if (DEBUG)
#define f first
#define s second
#define F0R(i, n) for(int i = 0; i < n; i++)
#define F0Ri(i, n) for(int i = 0; i <= n; i++)
#define F1R(i, n) for(int i = 1; i < n; i++)
#define F1Ri(i, n) for(int i = 1; i <= n; i++)
using namespace std;
using str = string;
using ll = long long;
#pragma endregion

struct buy {
    ll q, p;
    bool operator<(const buy& r) const {
        return p > r.p;
    }
};

int main() {
    MAIN_FILE_HEADER
    int N, M, R;
    cin >> N >> M >> R;
    vector<ll> gallons(N);
    vector<buy> buys(M);
    vector<ll> rents(R);
    F0R(i, N) {
        cin >> gallons.at(i);
    }
    sort(gallons.begin(), gallons.end(), greater<int>()); // Desc
    F0R(i, M) {
        cin >> buys.at(i).q >> buys.at(i).p;
    }
    sort(buys.begin(), buys.end()); // Desc (< overload >)
    F0R(i, R) {
        cin >> rents.at(i);
    }
    sort(rents.begin(), rents.end(), greater<int>()); // Desc
    vector<ll> pbuy(N, 0), prent(N, 0); // Prefix sum of buy (summed left to right) and rent (summed right to left)
    int j = 0;
    F0R(i, N) {
        if (i != 0) pbuy.at(i) = pbuy.at(i - 1);
        // Buy as much as possible
        while (j < M && gallons.at(i) > 0) {
            assert(j < M);
            int amount = min(gallons.at(i), buys.at(j).q);
            pbuy.at(i) += amount * buys.at(j).p;
            gallons.at(i) -= amount;
            buys.at(j).q -= amount;
            if (buys.at(j).q <= 0) j++;
            // if (j >= M) break;
        }
        dbg(pbuy.at(i) << " ")
    }
    dbgl(" ")
    // Rent as much as possible
    F0R(i, N) {
        auto ri = N - i - 1;
        if (i >= R) break;
        if (ri != N - 1) prent.at(ri) += prent.at(ri + 1);
        assert(i < R);
        prent.at(ri) += rents.at(i);
    }
    dbgs F0R(i, N) {
        dbg(prent.at(i) << " ")
    }
    dbgl(" ")
    // Find max pbuy[i] + prent[i + 1]
    ll ans = prent.at(0);
    F0R(i, N) {
        ans = max(ans, pbuy.at(i) + ((i >= N - 1) ? 0 : prent.at(i + 1)));
    }
    cout << ans << endl;
    return 0;
}