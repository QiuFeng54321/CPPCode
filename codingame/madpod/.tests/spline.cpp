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

#define DEBUG 1

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
    void outputReal(ostream& os) const { os << x << " " << y << " "; }
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
size_t cycle(int i, size_t n) { return (size_t)(i < 0 ? i + n : i % n); }
#pragma endregion

/* bezier-spline.js
 *
 * computes cubic bezier coefficients to generate a smooth
 * line through specified points. couples with SVG graphics
 * for interactive processing.
 *
 * For more info see:
 * http://www.particleincell.com/2012/bezier-splines/
 *
 * Lubos Brieda, Particle In Cell Consulting LLC, 2012
 * you may freely use this algorithm in your codes however where feasible
 * please include a link/reference to the source article
 *
 * correction by Jaco Stuifbergen:
 * in computeControlPoints:
 *	r[n-1] = 3*K[n-1]; // otherwise, the curvature on the last knot is wrong
 *
 * modification:
 * the distance of control points is proportional to the distance between knots
I.e. if D(x1,x2) is the distance between x1 and x2,
 and P1[i] , P2[i] are the control points between knots K[i] and K[i+1]
then
 D(P2[i-1],K[i]) / D(K[i-1],K[i]) = D(K[i],P1[i]) / D(K[i],K[i+1])
 */
struct Spline {
    Vec A, P1, P2, B;
    Vec AtTime(double t) const {
        var c = lerp(A, P1, t);
        var d = lerp(P1, P2, t);
        var e = lerp(P2, B, t);
        var f = lerp(c, d, t);
        var g = lerp(d, e, t);
        return lerp(f, g, t);
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
            frac_i = W[i] / W[cycle(i + 1, n)];
            a.pb(1 * W[i] * W[i]);
            b.pb(2 * W[cycle(i - 1, n)] * (W[cycle(i - 1, n)] + W[i]));
            c.pb(W[cycle(i - 1, n)] * W[cycle(i - 1, n)] *
                 frac_i);  // W[i]/W[i+1];
            r.pb(pow(W[cycle(i - 1, n)] + W[i], 2) * K[i] +
                 pow(W[cycle(i - 1, n)], 2) * (1 + frac_i) *
                     K[cycle(i + 1, n)]);
        }
        var p1 = ThomasCircular(r, a, b, c);
        for (var i = 0; i < n; i++) {  // p2[i]=2*K[i+1]-p1[i+1];
            p2[i] = K[cycle(i + 1, n)] * (1 + W[i] / W[cycle(i + 1, n)]) -
                    p1[cycle(i + 1, n)] * (W[i] / W[cycle(i + 1, n)]);
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
    Polybezier(vector<Vec> points, bool circular = true, double minWeight = 1) : Vertices(points), MinWeight(minWeight), IsCircular(circular) {}
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

int main() {
    Polybezier curve({{0, 0}, {4000, 6000}, {-3000, 10000}, {14000, -2000}, {3000, -9000}}, true, 1);
    curve.Generate();
    cout << "Hi\n";
    for (car point : curve.BakeTime(10)) {
        point.outputReal(cout);
    }
}