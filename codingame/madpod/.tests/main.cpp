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

#pragma region Helpers
struct Vec {
    double x, y;
    double abs() { return sqrt(x * x + y * y); }
    double angle() { return atan2(y, x); }
    // double angle(Vec base) { return atan2(det(base), dot(base)); }
    double angle(Vec base) { return angle() - base.angle(); }
    double dot(Vec b) { return x * b.x + y * b.y; }
    double det(Vec b) { return x * b.y - y * b.x; }
    Vec unit() { return operator/(abs()); }
    Vec rotate(double rad) {
        auto s = sin(rad), c = cos(rad);
        return {x * c - y * s, x * s + y * c};
    }
    friend ostream& operator<<(ostream& os, ctr(Vec) p) {
        os << (int)p.x << ' ' << (int)p.y;
        return os;
    }
    friend istream& operator>>(istream& os, Vec& p) {
        os >> p.x >> p.y;
        return os;
    }
    Vec operator+(Vec b) { return {x + b.x, y + b.y}; }
    Vec operator-(Vec b) { return {x - b.x, y - b.y}; }
    Vec operator*(double s) { return {x * s, y * s}; }
    Vec operator/(double s) { return {x / s, y / s}; }
};
struct PIDParams {
    double p, i, d;
};
class PIDController {
    PIDParams params;
    double prevError, integral;

   public:
    PIDController(PIDParams params) : params(params) {}
    PIDController(double p, double i, double d) : params({p, i, d}) {}
    double update(double error, double dt = 1) {
        var dx = (error - prevError) / dt;
        integral += error * dt;
        prevError = error;
        return params.p * error + params.i * integral + params.d * dx;
    }
};
const PIDParams AngleParams{0.25, 0.003, 0};

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

#pragma endregion

const auto cpdia = 1200;
Vec selfPos, oppPos, cpPos;
int cpDist, cpAngle;
ll timer = 0;
double lastAngle;
Vec lastPos;

struct GameParams {
    ll tick;
    Vec checkpointPos, opponentPos;
    queue<Vec> checkpoints;
    bool checkpointsRecorded;
    int currentCheckpointIndex;
};

class Pod {
    PIDController anglePID;
    Vec pos, lastPos;
    Vec targetPos;
    double thrust;
    bool boosted;
    int shieldCd;
    GameParams* gameParams;

   public:
    Pod(GameParams* gameParams)
        : anglePID(AngleParams), gameParams(gameParams) {}
    virtual void update(Vec newPos, Vec oppPos, Vec cpPos){};
    virtual void output(ctr(ostream) os){};
};
class RunnerPod : public Pod {
   public:
    RunnerPod(GameParams* gameParams) : Pod(gameParams) {}
    void update(Vec newPos, Vec oppPos, Vec cpPos) override{

    };
};
GameParams gameParams;
Pod* pod = new RunnerPod(&gameParams);
Vec getDestPos() {
    if (abs(cpAngle) > 90 || abs(cpAngle) < 5) return cpPos;
    const int effectiveRange = cpdia * 4;
    auto dirVec = cpPos - selfPos;
    auto velVec = selfPos - lastPos;
    cerr << "dir: " << dirVec << endl;
    cerr << "Vel: " << velVec << endl;

    auto deflectAngle = deg2rad(
        bound<double>(lerp<double>(lastAngle, cpAngle, 0.5) * 5, -90, 90));
    return selfPos + dirVec.rotate(deflectAngle);
}

Vec fixDrift(Vec destPos) {
    auto velVec = selfPos - lastPos;
    auto dirVec = cpPos - selfPos;
    auto angleDiff = velVec.angle(dirVec);
    if (abs(rad2deg(angleDiff)) > 45) return destPos;
    cerr << "Angle diff: " << rad2deg(angleDiff) << endl;

    return selfPos + (destPos - selfPos).rotate(-angleDiff * 0.25);
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
            lastPos = selfPos;
        }
        cerr << lastPos << " -> " << selfPos << endl;
        maxDist = max(maxDist, cpDist);
        const int check = cpdia * 3;
        auto normDistDiff =
            normalize<double>(bound(check - cpDist, 0, check), 0, check);
        auto decTh = (int)denormalize<double>(sinn(normDistDiff), 0, 50);
        auto decDegTh = 0;
        const int angleDecceleration = 45;
        const double angleDecFactor = 2.0;
        if (abs(cpAngle) > angleDecceleration) {
            decDegTh = angleDecFactor *
                       mapVal(bound(abs(cpAngle), angleDecceleration, 180),
                              angleDecceleration, 180, 0, 80);
        }
        auto resThrust = bound(100 - decDegTh - decTh, 20, 100);
        auto tarPos = fixDrift(getDestPos());
        // auto tarPos = fixDrift(cpPos);
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
        cout << endl;
        lastAngle = cpAngle;
        timer++;
        lastPos = selfPos;
    }
}