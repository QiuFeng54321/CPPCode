#include <iostream>
const int N = 10;
int vertex[4 * N];
int a[N] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

void build(int v, int l, int r) {
    if (l == r) {
        vertex[v] = a[l];
    } else {
        int m = (l + r) / 2;
        build(v * 2, l, m);
        build(v * 2 + 1, m + 1, r);
        vertex[v] = vertex[v * 2] + vertex[v * 2 + 1];
    }
}

void update(int i, int val, int l, int r, int v) {
    if (l == r) {
        a[i] = vertex[v] = val;
    } else {
        int m = (l + r) / 2;
        if (i <= m) {
            update(i, val, l, m, v * 2);
        } else {
            update(i, val, m + 1, r, v * 2 + 1);
        }
        vertex[v] = vertex[v * 2] + vertex[v * 2 + 1];
    }
}

int query(int v, int vl, int vr, int ql, int qr) {
    if (vl == ql && vr == qr) return vertex[v];
    int m = (vl + vr) / 2;
    if (qr <= m) return query(v * 2, vl, m, ql, qr);
    if (ql > m) return query(v * 2 + 1, m + 1, vr, ql, qr);
    return query(v * 2, vl, m, ql, m) + query(v * 2 + 1, m + 1, vr, m + 1, qr);
}

int main() {
    build(1, 0, N - 1);
    char c; 
    while ((c = std::cin.get()) != 'Q') {
        if (c == 'q') {
            int l, r;
            std::cin >> l >> r;
            std::cout << "a[" << l << ".." << r << "] = " << query(1, 0, N - 1, l, r);
        }
        if (c == 'u') {
            int i, v;
            std::cin >> i >> v;
            update(i, v, 0, N - 1, 1);
        }
    }
}