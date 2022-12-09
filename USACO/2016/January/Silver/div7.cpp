#include <fstream>
#include <iostream>


int main() {
    std::ifstream fin("div7.in");
    std::ofstream fout("div7.out");
    int N;
    fin >> N;
    int cows[N];
    for(int i = 0; i < N; i++) {
        fin >> cows[i];
        if (i != 0) cows[i] += cows[i - 1];
        cows[i] %= 7;
        // std::cout << cows[i] << " ";
    }
    int max_number = 0;
    for (int i = 0; i < N && N - 1 - i >= max_number; i ++) {
        for (int j = N - 1; j > i && j - i >= max_number; j--) {
            if ((cows[j] - cows[i]) % 7 == 0) {
                max_number = std::max(max_number, j - i);
                break;
            }
        }
    }
    fout << max_number;
}