using ll = long long;
struct Vec2D {
    ll x, y;
    int segindex;
};
struct Segment {
    Vec2D a, b;
    int index;
};

bool operator<(Vec2D p1, Vec2D p2) {
    return p1.x == p2.x ? p1.y < p2.y : p1.x < p2.x;
}

// Intersection testing (here, using a standard "cross product" trick)
int sign(ll x) {
    if (x == 0) return 0;
    return x < 0 ? -1 : +1;
}
int operator*(Vec2D p1, Vec2D p2) { return sign(p1.x * p2.y - p1.y * p2.x); }
Vec2D operator-(Vec2D p1, Vec2D p2) {
    Vec2D p = {p1.x - p2.x, p1.y - p2.y};
    return p;
}
bool isect(Segment &s1, Segment &s2) {
    Vec2D &A = s1.a, &B = s1.b, &C = s2.a, &D = s2.b;
    return ((D - A) * (B - A)) * ((B - A) * (C - A)) >= 0 &&
           ((B - C) * (D - C)) * ((D - C) * (A - C)) >= 0;
}