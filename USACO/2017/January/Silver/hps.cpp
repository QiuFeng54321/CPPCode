#include <fstream>
#include <iostream>

int main() {
    std::ifstream fin("hps.in");
    std::ofstream fout("hps.out");
    int N;
    fin >> N;
    char c;
    int prefixes[N + 1][3];
    for (int k = 0; k < 3; k++) prefixes[0][k] = 0;
    for (int i = 1; i < N + 1; i++) {
        for (int k = 0; k < 3; k++) prefixes[i][k] = prefixes[i - 1][k];
        fin >> c;
        int j = c == 'H' ? 0 : c == 'P' ? 1 : 2;
        prefixes[i][j] = prefixes[i - 1][j] + 1;
        // for (int k = 0; k < 3; k++) std::cout << "I(" << i << "), K(" << k << "): " << prefixes[i][k] << std::endl;
    }
    int wins = 0;
    // No gesture switch
    for (int i = 0; i < 3; i++) {
        wins = std::max(wins, prefixes[N][i]);
    }
    // With gesture switch
    for (int i = 1; i < N; i++) {  // (0 .. N - 1)
        int win = 0;
        for (int j = 0; j < 3; j++) { // before
            win = std::max(win, prefixes[i][j]);
        }
        for (int j = 0; j < 3; j++) { // after
            wins = std::max(wins, win + prefixes[N][j] - prefixes[i][j]);
        }
    }
    fout << wins;
}