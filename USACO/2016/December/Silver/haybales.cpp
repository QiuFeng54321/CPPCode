#include <fstream>
#include <iostream>
#include <algorithm>

int main() {
    std::ifstream fin("haybales.in");
    std::ofstream fout("haybales.out");
    int N, Q;
    fin >> N >> Q;
    int bales[N];
    for (int i = 0; i < N; i++ ) {
        fin >> bales[i];
    }
    std::sort(bales, bales + N);
    for (int i = 0; i < Q; i++) {
        int lower, upper, min = INT32_MAX, max = INT32_MIN;
        fin >> lower >> upper;
        for (int ind1 = (N + 1) / 2, ind2 = (N + 1) / 2, factor = N / 2; factor != 0; factor /= 2) {
            if (lower <= bales[ind1] && bales[ind1] <= upper) {
                min = std::min(min, ind1);
                ind1 -= factor;
            } else {
                ind1 += factor;
            }
            if (lower <= bales[ind2] && bales[ind2] <= upper) {
                max = std::max(max, ind2);
                ind2 += factor;
            } else {
                ind2 -= factor;
            }
        }
        std::cout << min << " " << max << std::endl;
    }
}