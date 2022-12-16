#define PROGRAM_NAME "${ProgramName}"
#include <algorithm>
#include <cmath>
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

struct Point {
    int x, y;
    double abs() { return sqrt(x * x + y * y); }
    double angle() { return atan(y / x); }
    Point rotate(double rad) {
        auto s = sin(rad), c = cos(rad);
        return {int(x * c - y * s), int(x * s + y * c)};
    }
    friend ostream& operator<<(ostream& os, ctr(Point) p) {
        os << p.x << ' ' << p.y;
        return os;
    }
    friend istream& operator>>(istream& os, Point& p) {
        os >> p.x >> p.y;
        return os;
    }
    Point operator+(Point b) { return {x + b.x, y + b.y}; }
    Point operator-(Point b) { return {x - b.x, y - b.y}; }
};

template <typename T>
T bound(T v, T lb, T ub) {
    return max(lb, min(ub, v));
}
template <typename T>
T mapVal(T v, T a, T b, T c, T d) {
    return (T)(c + ((double)(d - c)) * (v - a) / (b - a));
}
template <typename T>
T normalize(T v, T a, T b) {
    return mapVal<T>(v, a, b, 0, 1);
}
template <typename T>
T denormalize(T v, T a, T b) {
    return mapVal<T>(v, 0, 1, a, b);
}

template <typename T>
T lerp(T a, T b, double t) {
    return (T)(a + (b - a) * t);
}
double deg2rad(double deg) { return deg * (M_PI / 180); }
double rad2deg(double rad) { return rad * 180 / M_PI; }
double sinn(double x) { return sin(x * M_PI / 2); }  // [0..1] maps to [0..1]

const auto cpdia = 1200;
Point selfPos, oppPos, cpPos;
int cpDist, cpAngle;
ll timer = 0;
double lastAngle;

Point getDestPos() {
    if (abs(cpAngle) > 90 || abs(cpAngle) < 5) return cpPos;
    const int effectiveRange = cpdia * 4;
    auto dirVec = cpPos - selfPos;

    auto deflectAngle = deg2rad(bound<double>(lerp<double>(lastAngle, cpAngle, 0.5) * 5, -90, 90));
    return selfPos + dirVec.rotate(deflectAngle);
}

int main() {
    bool boostUsed = false;
    int maxDist = 0;
    // game loop
    while (1) {
        cin >> selfPos >> cpPos >> cpDist >> cpAngle >> oppPos;
        cin.ignore();
        if (!timer) {
            lastAngle = cpAngle;
        }
        maxDist = max(maxDist, cpDist);
        const int check = cpdia * 3;
        auto normDistDiff =
            normalize<double>(bound(check - cpDist, 0, check), 0, check);
        auto decTh = (int)denormalize<double>(sinn(normDistDiff), 0, 80);
        auto decDegTh = 0;
        const int angleDecceleration = 45;
        const double angleDecFactor = 2.0;
        if (abs(cpAngle) > angleDecceleration) {
            decDegTh = angleDecFactor *
                       mapVal(bound(abs(cpAngle), angleDecceleration, 180),
                              angleDecceleration, 180, 0, 80);
        }
        auto resThrust = bound(100 - decDegTh - decTh, 20, 100);
        auto tarPos = getDestPos();
        cerr << cpAngle << ": " << tarPos << endl;
        cerr << normDistDiff << ", " << decTh << endl;
        cout << tarPos << " ";

        if (!boostUsed && maxDist > cpdia * 4 && maxDist - cpDist < 300 &&
            abs(cpAngle) <= 5 && resThrust > 90) {
            boostUsed = true;
            cout << "BOOST";
        } else {
            cout << resThrust;
        }
        lastAngle = cpAngle;
        cout << endl;
        timer++;
    }
}