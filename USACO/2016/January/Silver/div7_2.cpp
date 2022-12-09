#include <fstream>
// #include <iostream>

int main() {
    std::ifstream fin("div7.in");
    std::ofstream fout("div7.out");
    int N;
    fin >> N;
    int least[7] = {INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX}, 
        most[7] = {0, 0, 0, 0, 0, 0, 0};
    int num, n;
    for(int i = 0; i < N; i ++) {
        fin >> n;
        num += n;
        num %= 7;
        least[num] = std::min(least[num], i);
        most[num] = std::max(most[num], i);
        // std::cout << num << ", least(" << least[num] << "), most(" << most[num] << ")" << std::endl;
    }
    int max = 0;
    for(int i = 0; i < 7; i++) {
        max = std::max(most[i] - least[i], max);
    }
    fout << max;
}