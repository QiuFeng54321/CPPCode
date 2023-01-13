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
bool FpEqual(T a, T b) {
    return abs(a - b) < eps;
}

template <typename T>
T Bound(T v, T lb, T ub) {
    return max(lb, min(ub, v));
}
template <typename T>
T MapVal(T v, T a, T b, T c, T d) {
    return (T)(c + ((double)(d - c)) * (v - a) / (b - a));
}
template <typename T>
T Normalize(T v, T a, T b) {
    return MapVal<T>(v, a, b, 0, 1);
}
template <typename T>
T Denormalize(T v, T a, T b) {
    return MapVal<T>(v, 0, 1, a, b);
}

template <typename T>
T Lerp(T a, T b, double t) {
    return (T)(a + (b - a) * t);
}
double DegToRad(double deg) { return deg * (M_PI / 180); }
double RadToDeg(double rad) { return rad * 180 / M_PI; }
double SinN(double x) { return sin(x * M_PI / 2); }  // [0..1] maps to [0..1]
size_t Cycle(int i, size_t n) { return (size_t)(i < 0 ? i + n : i % n); }
struct Vec {
    double x, y;
    double Abs() const { return sqrt(SqDist()); }
    double Angle() const { return atan2(y, x); }
    // double angle(Vec base) { return atan2(Det(base), dot(base)); }
    double Angle(Vec base) const { return Angle() - base.Angle(); }
    double Dot(Vec b) const { return x * b.x + y * b.y; }
    double Det(Vec b) const { return x * b.y - y * b.x; }
    double SqDist() const { return x * x + y * y; }
    double SqDist(Vec b) const { return operator-(b).SqDist(); };
    Vec Unit() const { return operator/(Abs()); }
    Vec Rotate(double rad) const {
        auto s = sin(rad), c = cos(rad);
        return {x * c - y * s, x * s + y * c};
    }
    void OutputReal(ostream& os) { os << "(" << x << ", " << y << ")"; }
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
    bool operator==(Vec b) const { return FpEqual(x, b.x) && FpEqual(y, b.y); }
    bool operator!=(Vec b) const { return !operator==(b); }
};
struct Spline {
    Vec A, P1, P2, B;
    Vec AtTime(double t) const {
        var c = Lerp(A, P1, t);
        var d = Lerp(P1, P2, t);
        var e = Lerp(P2, B, t);
        var f = Lerp(c, d, t);
        var g = Lerp(d, e, t);
        return Lerp(f, g, t);
    }
};
// http://www.jacos.nl/jacos_html/spline/circular/index.html
class Polybezier {
    using vd = vector<double>;
    using pxy = pair<vd, vd>;
    vector<Spline> Splines;
    vector<Vec> Vertices;

   public:
    double MinWeight = 1;
    bool IsCircular = true;

   protected:
    vd ThomasCircular(vd r, vd a, vd b, vd c) {
        double m;
        var n = r.size();
        vd lc(n);
        lc[0] = a[0];
        var lr = c[n - 1];
        var i = 0;
        for (; i < n - 3; i++) {
            m = a[i + 1] / b[i];
            b[i + 1] -= m * c[i];
            r[i + 1] -= m * r[i];
            lc[i + 1] = -m * lc[i];
            m = lr / b[i];
            b[n - 1] -= m * lc[i];
            lr = -m * c[i];
            r[n - 1] -= m * r[i];
        }
        {
            m = a[i + 1] / b[i];
            b[i + 1] -= m * c[i];
            r[i + 1] -= m * r[i];
            c[i + 1] -= m * lc[i];
            m = lr / b[i];
            b[n - 1] -= m * lc[i];
            a[n - 1] -= m * c[i];
            r[n - 1] = r[n - 1] - m * r[i];
        }
        i = n - 2;
        {
            m = a[i + 1] / b[i];
            b[i + 1] -= m * c[i];
            r[i + 1] -= m * r[i];
        }
        vd x(n);
        x[n - 1] = r[n - 1] / b[n - 1];
        lc[n - 2] = 0;
        for (i = n - 2; i >= 0; --i) {
            x[i] = (r[i] - c[i] * x[i + 1] - lc[i] * x[n - 1]) / b[i];
        }
        return x;
    }

    /* return x and y values of knots */
    pxy ZipCoords() {
        pxy res;
        for (car[x, y] : Vertices) {
            res.first.push_back(x);
            res.second.push_back(y);
        }
        return res;
    }
    pxy ComputeCPCircW(vd K, vd W) {
        double frac_i;
        var n = K.size();
        vd p2(n);
        /*rhs vector*/
        vd a, b, c, r;
        for (var i = 0; i < n; i++) {
            frac_i = W[i] / W[Cycle(i + 1, n)];
            a.pb(1 * W[i] * W[i]);
            b.pb(2 * W[Cycle(i - 1, n)] * (W[Cycle(i - 1, n)] + W[i]));
            c.pb(W[Cycle(i - 1, n)] * W[Cycle(i - 1, n)] *
                 frac_i);  // W[i]/W[i+1];
            r.pb(pow(W[Cycle(i - 1, n)] + W[i], 2) * K[i] +
                 pow(W[Cycle(i - 1, n)], 2) * (1 + frac_i) *
                     K[Cycle(i + 1, n)]);
        }
        var p1 = ThomasCircular(r, a, b, c);
        for (var i = 0; i < n; i++) {  // p2[i]=2*K[i+1]-p1[i+1];
            p2[i] = K[Cycle(i + 1, n)] * (1 + W[i] / W[Cycle(i + 1, n)]) -
                    p1[Cycle(i + 1, n)] * (W[i] / W[Cycle(i + 1, n)]);
        }
        return {p1, p2};
    }
    double Weighting(double x1, double x2, double y1, double y2) {
        /* calculate Euclidean distance */
        var d = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
        // if the weight is too small, the calculation becomes instable
        return d < MinWeight ? MinWeight : d;
    }
    /*computes spline control points*/
    void UpdateSplines() {
        Splines.clear();
        var[x, y] = ZipCoords();
        var nKnots = Vertices.size();
        vd weights(nKnots);
        for (var i = 0; i < nKnots; i++) {
            weights[i] =
                Weighting(x[(i + 1) % nKnots], x[i], y[(i + 1) % nKnots], y[i]);
        }
        var px = ComputeCPCircW(x, weights);
        var py = ComputeCPCircW(y, weights);
        var i = 0;
        for (; i < nKnots - 1; i++) {
            Splines.pb(Spline{{x[i], y[i]},
                              {px.first[i], py.first[i]},
                              {px.second[i], py.second[i]},
                              {x[i + 1], y[i + 1]}});
        }
        if (IsCircular)  // for circular loops
        {
            Splines.pb(Spline{{x[i], y[i]},
                              {px.first[i], py.first[i]},
                              {px.second[i], py.second[i]},
                              {x[0], y[0]}});
        }
    }

   public:
    Polybezier(vector<Vec> points, bool circular = true, double minWeight = 1)
        : Vertices(points), MinWeight(minWeight), IsCircular(circular) {}
    void AddPoint(Vec p) { Vertices.push_back(p); }
    void Generate() { UpdateSplines(); }
    vector<Vec> BakeTime(int samples) {
        vector<Vec> bakedPoints;
        if (samples < 2) return bakedPoints;
        double interval = 1.0 / (samples - 1);
        for (var j = 0; j < Splines.size(); j++) {
            car spline = Splines[j];
            if (!j) bakedPoints.push_back(spline.AtTime(0));
            for (var i = 1; i < samples; i++) {
                bakedPoints.push_back(spline.AtTime(i * interval));
            }
        }
        return bakedPoints;
    }
};
struct PIDParams {
    double p, i, d;
};
class PIDController {
    PIDParams Params;
    double PrevError, Integral;

   public:
    PIDController(PIDParams params) : Params(params) {}
    PIDController(double p, double i, double d) : Params({p, i, d}) {}
    double Update(double error, double dt = 1) {
        var dx = (error - PrevError) / dt;
        Integral += error * dt;
        PrevError = error;
        return Params.p * error + Params.i * Integral + Params.d * dx;
    }
    void Reset() {
        Integral = 0;
        PrevError = 0;
    }
};
#pragma endregion

struct Checkpoint;
struct GameState;
class Entity;
class Enemy;
class Pod;
class RunnerPod;

struct Checkpoint {
    Vec Pos;
    Checkpoint *Next = nullptr, *Prev = nullptr;
};
struct GameState {
    ll Tick;
    Vec CheckpointPos;
    int CheckpointDist, CheckpointAngle;
    Checkpoint *StartCp, *CurrentCp, *MaxDistCp;
    bool CheckpointsRecorded;
    int CurrentCheckpointIndex;
    vector<Enemy> Enemies;
    queue<Vec> SmoothPath;
};

const auto CPDia = 1200, PodDia = 800;
const PIDParams AngleParams{0.25, 0.005, -0.01};
GameState GameStates;

class Entity {
   public:
    Vec Pos, LastPos;
    Vec VelocityVec() const { return Pos - LastPos; }
    void UpdatePos(Vec p) {
        LastPos = Pos;
        Pos = p;
    }
    double WhenCollide(Entity another) {
        // https://gamedev.stackexchange.com/questions/97337/detect-if-two-objects-are-going-to-collide
        var b = VelocityVec();
        var d = another.VelocityVec();
        var dp = Pos - another.Pos;
        var dv = b - d;
        var mintime = -dp.Dot(dv) / dv.Dot(dv);
        var minsqdist = (dv * mintime + dp).SqDist();
        cerr << "Min time: " << mintime << endl;
        cerr << "Min dist: " << sqrt(minsqdist) << endl;
        if (mintime < 0 || minsqdist > PodDia * PodDia) return -1;
        return mintime;
    }
};
class Enemy : public Entity {};
class Pod : public Entity {
   public:
    PIDController AnglePID;
    Vec TargetPos, OutputPos;
    double Thrust;
    bool Boosted;
    int ShieldCd;
    bool BoostNextRound, ShieldNextRound;
    GameState* GameStates;
    double VelRadToCp;
    Vec TargetDirVec;

    Pod(GameState* gameStates)
        : AnglePID(AngleParams), GameStates(gameStates) {}
    virtual void Update(Vec newPos) { UpdatePos(newPos); };
    virtual void Output(ostream& os) {
        os << OutputPos << ' ';
        if (BoostNextRound) {
            os << "BOOST";
            Boosted = true;
            BoostNextRound = false;
        } else if (ShieldNextRound) {
            os << "SHIELD";
            ShieldCd = 3;
            ShieldNextRound = false;
        } else if (ShieldCd == 0) {
            os << Thrust;
        } else {
            os << 0;
            ShieldCd = max(0, ShieldCd - 1);
        }
        os << endl;
    };
    void ProcessAngle() {
        auto velVec = Pos - LastPos;
        TargetDirVec = TargetPos - Pos;
        VelRadToCp = velVec.Angle(TargetDirVec);
    }
    void ProcessThrust() {
        const int check = CPDia * 2;
        auto normDistDiff = Normalize<double>(
            Bound(check - GameStates->CheckpointDist, 0, check), 0, check);
        auto decTh = (int)(SinN(normDistDiff) * 50);
        auto decDegTh = 0;
        const int angleDecceleration = 45;
        const double angleDecFactor = 2.0;
        if (abs(GameStates->CheckpointAngle) > angleDecceleration) {
            decDegTh = (int)(MapVal(Bound(abs(GameStates->CheckpointAngle),
                                          angleDecceleration, 180),
                                    angleDecceleration, 180, 0, 100));
        }
        Thrust = Bound(100 - decDegTh - decTh, 0, 100);
    }

    void FixDrift() {
        if (abs(RadToDeg(VelRadToCp)) > 90) return;
        cerr << "Angle diff: " << RadToDeg(VelRadToCp) << endl;
        OutputPos =
            Pos + (TargetPos - Pos).Rotate(-AnglePID.Update(VelRadToCp));
    }
    void DealWithCollision() {
        if (ShieldCd > 0) return;
        for (car enemy : GameStates->Enemies) {
            var collisionTime = WhenCollide(enemy);
            if (collisionTime == -1 || collisionTime > 5) continue;
            var angleDiff = enemy.VelocityVec().Angle(TargetDirVec);
            if (abs(angleDiff) <= DegToRad(45)) continue;
            // TODO let the enemy collide if it's good for me
            ShieldNextRound = true;
        }
    }
};
class RunnerPod : public Pod {
   public:
    RunnerPod(GameState* gameStates) : Pod(gameStates) {}
    void Update(Vec newPos) override {
        Pod::Update(newPos);
        ProcessAngle();
        // TODO: Top of smooth path if possible
        TargetPos = GameStates->CheckpointPos;
        // deflectAngle();
        FixDrift();
        ProcessThrust();
        DecideBoost();
        TargetNext();
        DealWithCollision();
    }
    void DecideBoost() {
        if (Boosted) return;
        // if (!GameStates->checkpointsRecorded) return;
        // if (GameStates->currentCp != GameStates->maxDistCp) return;
        // if (abs(RadToDeg(VelRadToCp)) > 8) return;
        // if (GameStates->checkpointDist < CPDia * 3) return;
        BoostNextRound = true;
        TargetPos = GameStates->CheckpointPos;
    }
    void TargetNext() {
        if (!GameStates->CheckpointsRecorded) return;
        if (GameStates->CheckpointDist > CPDia) return;
        if (abs(VelRadToCp) > DegToRad(6)) return;
        TargetPos = GameStates->CurrentCp->Next->Pos;
    }
    void FindNextSmoothPath() {

    }
};

Pod* ActivePod = new RunnerPod(&GameStates);
void FindMaxDistCp() {
    GameStates.MaxDistCp = GameStates.StartCp;
    var cp = GameStates.StartCp;
    Polybezier smoothPath{{}};
    do {
        var angle = (cp->Pos - cp->Prev->Pos)
                        .Angle(cp->Prev->Pos - cp->Prev->Prev->Pos);
        var dist = cp->Pos.SqDist(cp->Prev->Pos);
        if (abs(angle) < DegToRad(30) || dist > pow(CPDia * 3, 2)) {
            if (dist > GameStates.MaxDistCp->Pos.SqDist(
                           GameStates.MaxDistCp->Prev->Pos)) {
                GameStates.MaxDistCp = cp;
            }
        }
        smoothPath.AddPoint(cp->Pos);
        cp = cp->Next;
    } while (cp != GameStates.StartCp);
    smoothPath.Generate();
    var nodes = smoothPath.BakeTime(10);
    for (car p : nodes) {
        GameStates.SmoothPath.push(p);
    }
}
void RecordCp() {
    if (!GameStates.CheckpointsRecorded) {
        if (GameStates.StartCp == nullptr) {
            GameStates.CurrentCp = GameStates.StartCp =
                new Checkpoint{GameStates.CheckpointPos};
        } else {
            if (GameStates.CurrentCp != GameStates.StartCp &&
                GameStates.StartCp->Pos == GameStates.CheckpointPos) {
                GameStates.CheckpointsRecorded = true;
                GameStates.CurrentCp->Next = GameStates.StartCp;
                GameStates.StartCp->Prev = GameStates.CurrentCp;
                // Find max distance cp
                FindMaxDistCp();
            } else if (GameStates.CurrentCp->Pos != GameStates.CheckpointPos) {
                GameStates.CurrentCp->Next =
                    new Checkpoint{GameStates.CheckpointPos};
                GameStates.CurrentCp->Next->Prev = GameStates.CurrentCp;
                GameStates.CurrentCp = GameStates.CurrentCp->Next;
            }
        }
    } else {
        cerr << "Reocrded: max " << GameStates.MaxDistCp->Pos << endl;
        while (GameStates.CurrentCp->Pos != GameStates.CheckpointPos) {
            // if (GameStates.currentCp == GameStates.maxDistCp &&
            // !ActivePod->Boosted)
            // {
            //     GameStates.maxDistCp = GameStates.maxDistCp->next;
            // }
            GameStates.CurrentCp = GameStates.CurrentCp->Next;
            ActivePod->AnglePID.Reset();
        }
    }
}
int main() {
    // game loop
    while (1) {
        if (!GameStates.Tick) {
            GameStates.Enemies.push_back(Enemy{});
        }
        Vec podPos;
        cin >> podPos >> GameStates.CheckpointPos >>
            GameStates.CheckpointDist >> GameStates.CheckpointAngle;
        for (Enemy& enemy : GameStates.Enemies) {
            Vec pos;
            cin >> pos;
            enemy.UpdatePos(pos);
        }
        cin.ignore();
        RecordCp();
        ActivePod->Update(podPos);
        ActivePod->Output(cout);
        GameStates.Tick++;
    }
}