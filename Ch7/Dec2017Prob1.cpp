#include <fstream>
#include <vector>

std::ifstream fin;
std::ofstream fout;

int opposite(int x) { return (x + 2) % 2; }

struct Vec2D {
    int x, y;
};

class Rect {
   public:
    Vec2D ll, ul, ur, lr;  // Arranged so vec[(i + 2) % 2] is always the
                           // opposite angle of vec[i]
    int hori_len, vert_len;
    int area;
    Rect(Vec2D ll, Vec2D ur) : ll(ll), ur(ur) { process(); }
    void process() {
        lr = Vec2D{ur.x, ll.y};
        ul = Vec2D{ll.x, ur.y};
        hori_len = abs(ll.x - ur.x);
        vert_len = abs(ll.y - ur.y);
        area = hori_len * vert_len;
    }
    bool in_range(Vec2D p) {
        return p.x < ur.x && p.x > ll.x && p.y < ur.y && p.y > ll.y;
    }
    bool axis_line_in_range(Vec2D b, Vec2D u) {
        if (b.x > ll.x && b.x < ur.x && b.y < ll.y && u.y > ur.y) return 1;
        if (b.y > ll.y && b.y < ur.y && b.x < ll.x && u.x > ur.x) return 2;
    }
    int overlap_area_1v(Rect rect, int v) {
        Vec2D diag = (*this)[opposite(v)];
        Vec2D from = rect[v];
        return Rect(from, diag).area;
    }
    int overlap_area_0v2o(
        Rect rect, int a, int b,
        int axis) {  // 0 vertex inside, 2 vertex outside but cuts the rect
        if (axis == 1) {
            Vec2D ori = rect[a];
            int upper_y = ((*this)[opposite(b)]).y;
            Vec2D opp = (*this)[opposite(a)];
            return Rect{{ori.x, upper_y}, opp}.area;
        } else {
            Vec2D ori = rect[a];
            int upper_x = ((*this)[opposite(b)]).x;
            Vec2D opp = (*this)[opposite(a)];
            return Rect{{upper_x, ori.y}, opp}.area;
        }
    }
    Vec2D& operator[](int index) {
        if (index == 0) return ll;
        if (index == 1) return ul;
        if (index == 2) return ur;
        return lr;
    }
};

void recordVec(Vec2D& vec) { fin >> vec.x >> vec.y; }

void recordRect(Rect* rect) {
    Vec2D ll, ur;
    recordVec(ll);
    recordVec(ur);
    rect = new Rect{ll, ur};
    rect->process();
}

int nonOverlapArea(Rect& Overlap, Rect& Back) {
    std::vector<int> overlap_vertexes;
    int overlap_area = 0;
    for (int i = 0; i < 4; i++) {
        for(int j = i + 1; j < 4; j++) {
            int axis = Back.axis_line_in_range(Overlap[i], Overlap[j]);
            if (axis) {
                return Back.overlap_area_0v2o(Overlap, i, j, axis);
            }
        }
        if (Back.in_range(Overlap[i])) overlap_vertexes.push_back(i);
    }
    if (overlap_vertexes.size() == 1) {  // one vertex overlap
        overlap_area = Back.overlap_area_1v(Overlap, overlap_vertexes[0]);
    }
}

int main() {
    fin = std::ifstream("billboard.in");
    fout = std::ofstream("billboard.out");
    Rect *B1, *B2, *T;
    recordRect(B1);
    recordRect(B2);
    recordRect(T);
}