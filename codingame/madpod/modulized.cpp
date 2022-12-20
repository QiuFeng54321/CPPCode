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
const double eps = 1e-5;
#pragma endregion

#pragma region Helpers
template <typename T>
bool fpEqual(T a, T b) {
    return abs(a - b) < eps;
}
struct Vec {
    double x, y;
    double abs() const { return sqrt(sqdist()); }
    double angle() const { return atan2(y, x); }
    // double angle(Vec base) { return atan2(det(base), dot(base)); }
    double angle(Vec base) const { return angle() - base.angle(); }
    double dot(Vec b) const { return x * b.x + y * b.y; }
    double det(Vec b) const { return x * b.y - y * b.x; }
    double sqdist() const { return x * x + y * y; }
    double sqdist(Vec b) const { return operator-(b).sqdist(); };
    Vec unit() const { return operator/(abs()); }
    Vec rotate(double rad) const {
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
    Vec operator+(Vec b) const { return {x + b.x, y + b.y}; }
    Vec operator-(Vec b) const { return {x - b.x, y - b.y}; }
    Vec operator-() const { return {-x, -y}; }
    Vec operator*(double s) const { return {x * s, y * s}; }
    Vec operator/(double s) const { return {x / s, y / s}; }
    bool operator==(Vec b) const { return fpEqual(x, b.x) && fpEqual(y, b.y); }
    bool operator!=(Vec b) const { return !operator==(b); }
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
    void reset() {
        integral = 0;
        prevError = 0;
    }
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

#pragma endregion

struct Checkpoint;
struct GameState;
class Entity;
class Enemy;
class Pod;
class RunnerPod;

struct Checkpoint {
    Vec pos;
    Checkpoint *next = nullptr, *prev = nullptr;
};
struct GameState {
    ll tick;
    Vec checkpointPos;
    int checkpointDist, checkpointAngle;
    Checkpoint *startCp, *currentCp, *maxDistCp;
    bool checkpointsRecorded;
    int currentCheckpointIndex;
    vector<Enemy> enemies;
};

const auto cpdia = 1200, poddia = 800;
const PIDParams AngleParams{0.25, 0.005, -0.01};
GameState gameState;

class Entity {
   public:
    Vec pos, lastPos;
    Vec velocityVec() const { return pos - lastPos; }
    void updatePos(Vec p) {
        lastPos = pos;
        pos = p;
    }
    double whenCollide(Entity another) {
        // https://gamedev.stackexchange.com/questions/97337/detect-if-two-objects-are-going-to-collide
        var b = velocityVec();
        var d = another.velocityVec();
        var dp = pos - another.pos;
        var dv = b - d;
        var mintime = -dp.dot(dv) / dv.dot(dv);
        var minsqdist = (dv * mintime + dp).sqdist();
        cerr << "Min time: " << mintime << endl;
        cerr << "Min dist: " << sqrt(minsqdist) << endl;
        if (mintime < 0 || minsqdist > poddia * poddia) return -1;
        return mintime;
    }
};
class Enemy : public Entity {};
class Pod : public Entity {
   public:
    PIDController anglePID;
    Vec targetPos;
    double thrust;
    bool boosted;
    int shieldCd;
    bool boostNextRound, shieldNextRound;
    GameState* gameState;
    double velRadToCp;
    Vec targetDirVec;

    Pod(GameState* gameState) : anglePID(AngleParams), gameState(gameState) {}
    virtual void update(Vec newPos) { updatePos(newPos); };
    virtual void output(ostream& os) {
        os << targetPos << ' ';
        if (boostNextRound) {
            os << "BOOST";
            boosted = true;
            boostNextRound = false;
        } else if (shieldNextRound) {
            os << "SHIELD";
            shieldCd = 3;
            shieldNextRound = false;
        } else if (shieldCd == 0) {
            os << thrust;
        } else {
            os << 0;
            shieldCd = max(0, shieldCd - 1);
        }
        os << endl;
    };
    void processAngle() {
        auto velVec = pos - lastPos;
        targetDirVec = gameState->checkpointPos - pos;
        velRadToCp = velVec.angle(targetDirVec);
    }
    void processThrust() {
        const int check = cpdia * 2;
        auto normDistDiff = normalize<double>(
            bound(check - gameState->checkpointDist, 0, check), 0, check);
        auto decTh = (int)(sinn(normDistDiff) * 50);
        auto decDegTh = 0;
        const int angleDecceleration = 45;
        const double angleDecFactor = 2.0;
        if (abs(gameState->checkpointAngle) > angleDecceleration) {
            decDegTh = (int)(angleDecFactor *
                             mapVal(bound(abs(gameState->checkpointAngle),
                                          angleDecceleration, 180),
                                    angleDecceleration, 180, 0, 80));
        }
        thrust = bound(100 - decDegTh - decTh, 0, 100);
    }
    void deflectAngle() {
        if (abs(velRadToCp) > M_PI_2 || abs(velRadToCp) < deg2rad(5)) return;
        auto dirVec = gameState->checkpointPos - pos;
        auto velVec = pos - lastPos;
        cerr << "dir: " << dirVec << endl;
        cerr << "Vel: " << velVec << endl;
        auto deflectAngle = bound<double>(velRadToCp * 5, -M_PI_2, M_PI_2);
        targetPos = pos + dirVec.rotate(deflectAngle);
    }

    void fixDrift() {
        if (abs(rad2deg(velRadToCp)) > 90) return;
        cerr << "Angle diff: " << rad2deg(velRadToCp) << endl;
        targetPos =
            pos + (targetPos - pos).rotate(-anglePID.update(velRadToCp));
    }
    void dealWithCollision() {
        if (shieldCd > 0) return;
        for (car enemy : gameState->enemies) {
            var collisionTime = whenCollide(enemy);
            if (collisionTime == -1 || collisionTime > 6) continue;
            var angleDiff = enemy.velocityVec().angle(targetDirVec);
            if (abs(angleDiff) <= deg2rad(30)) continue;
            // TODO let the enemy collide if it's good for me
            shieldNextRound = true;
        }
    }
};
class RunnerPod : public Pod {
   public:
    RunnerPod(GameState* gameState) : Pod(gameState) {}
    void update(Vec newPos) override {
        Pod::update(newPos);
        processAngle();
        targetPos = gameState->checkpointPos;
        // deflectAngle();
        fixDrift();
        processThrust();
        decideBoost();
        targetNext();
        dealWithCollision();
    }
    void decideBoost() {
        if (boosted) return;
        // if (!gameState->checkpointsRecorded) return;
        // if (gameState->currentCp != gameState->maxDistCp) return;
        // if (abs(rad2deg(velRadToCp)) > 8) return;
        // if (gameState->checkpointDist < cpdia * 3) return;
        boostNextRound = true;
        targetPos = gameState->checkpointPos;
    }
    void targetNext() {
        if (!gameState->checkpointsRecorded) return;
        if (gameState->checkpointDist > cpdia) return;
        if (abs(velRadToCp) > deg2rad(6)) return;
        targetPos = gameState->currentCp->next->pos;
    }
};

Pod* pod = new RunnerPod(&gameState);
void find_max_dist_cp() {
    gameState.maxDistCp = gameState.startCp;
    var cp = gameState.startCp;
    do {
        var angle = (cp->pos - cp->prev->pos)
                        .angle(cp->prev->pos - cp->prev->prev->pos);
        var dist = cp->pos.sqdist(cp->prev->pos);
        if (abs(angle) < deg2rad(30) || dist > pow(cpdia * 3, 2)) {
            if (dist > gameState.maxDistCp->pos.sqdist(
                           gameState.maxDistCp->prev->pos)) {
                gameState.maxDistCp = cp;
            }
        }
        cp = cp->next;
    } while (cp != gameState.startCp);
}
void record_cp() {
    if (!gameState.checkpointsRecorded) {
        if (gameState.startCp == nullptr) {
            gameState.currentCp = gameState.startCp =
                new Checkpoint{gameState.checkpointPos};
        } else {
            if (gameState.currentCp != gameState.startCp &&
                gameState.startCp->pos == gameState.checkpointPos) {
                gameState.checkpointsRecorded = true;
                gameState.currentCp->next = gameState.startCp;
                gameState.startCp->prev = gameState.currentCp;
                // Find max distance cp
                find_max_dist_cp();
            } else if (gameState.currentCp->pos != gameState.checkpointPos) {
                gameState.currentCp->next =
                    new Checkpoint{gameState.checkpointPos};
                gameState.currentCp->next->prev = gameState.currentCp;
                gameState.currentCp = gameState.currentCp->next;
            }
        }
    } else {
        cerr << "Reocrded: max " << gameState.maxDistCp->pos << endl;
        while (gameState.currentCp->pos != gameState.checkpointPos) {
            // if (gameState.currentCp == gameState.maxDistCp && !pod->boosted)
            // {
            //     gameState.maxDistCp = gameState.maxDistCp->next;
            // }
            gameState.currentCp = gameState.currentCp->next;
            pod->anglePID.reset();
        }
    }
}
int main() {
    // game loop
    while (1) {
        if (!gameState.tick) {
            gameState.enemies.push_back(Enemy{});
        }
        Vec podPos;
        cin >> podPos >> gameState.checkpointPos >> gameState.checkpointDist >>
            gameState.checkpointAngle;
        for (Enemy& enemy : gameState.enemies) {
            Vec pos;
            cin >> pos;
            enemy.updatePos(pos);
        }
        cin.ignore();
        record_cp();
        pod->update(podPos);
        pod->output(cout);
        gameState.tick++;
    }
}