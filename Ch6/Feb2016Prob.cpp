#include <fstream>

int main() {
    std::ifstream fin("pails.in");
    std::ofstream fout("pails.out");
    int X, Y, N;
    fin >> X >> Y >> N;
    int min_remaining = INT32_MAX;
    int loop_times = (N - N % X) / X;
    for(int i = 0; i < loop_times; i++) {
        int Xs = (loop_times - i) * X;
        int remaining = (N - Xs) % Y;
        min_remaining = std::min(min_remaining, remaining);
    }
}