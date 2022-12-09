#include <iostream>
class S {
   public:
    int a, b, c;
    bool d;
    int arrr[4][5];
    void set(int i) { d = i; }
};

bool test(S s) {
    s.b = 3;
    return s.a;
}
bool test2(S* s) {
    (*s).b = 3;
    return s->a;
}
long arr[3][3]{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int p() {
    auto l = arr[1][2];
    return 0;
    // int* iptr = arr;
    // for (int i = 0; i < 2; i++) {
    // arr[i][(i + 2) % 2] = arr[i + 1][i];
    // }
}
int main() {
    p();
    return 0;
}
