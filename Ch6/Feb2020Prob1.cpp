#include <cmath>
#include <fstream>
#include <iostream>

/*
ID: qiufeng
TASK: triangles
LANG: C++
*/

using namespace std;

struct Vec2D {
    int x, y;
};

bool parallel(Vec2D A, Vec2D B) { return A.x == B.x || A.y == B.y; }

int straight_dist(Vec2D A, Vec2D B) { return abs((B.x - A.x) + (B.y - A.y)); }

int area(int x, int y) {
    // In the end the result is multiplied by 2, so the denominator eliminates
    // here
    return x * y;
}

int main() {
    ifstream fin("triangles.in");
    ofstream fout("triangles.out");
    int N;
    fin >> N;
    Vec2D coords[N];
    for (int i = 0; i < N; i++) {
        Vec2D vec;
        fin >> vec.x >> vec.y;
        coords[i] = vec;
    }
    int max_area = -1;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                Vec2D A = coords[i], B = coords[j], C = coords[k];
                int distA, distB;
                if (parallel(A, B) && parallel(A, C)) {
                    distA = straight_dist(A, B);
                    distB = straight_dist(A, C);
                } else if (parallel(C, B) && parallel(C, A)) {
                    distA = straight_dist(C, B);
                    distB = straight_dist(C, A);
                } else if (parallel(B, A) && parallel(B, C)) {
                    distA = straight_dist(B, A);
                    distB = straight_dist(B, C);
                }
                max_area = max(max_area, area(distA, distB));
            }
        }
    }
    fout << max_area << endl;
}