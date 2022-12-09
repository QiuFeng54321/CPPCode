#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int desc_cmp(int x, int y) {
    return x > y;
}

int main() {
    ifstream fin("lemonade_silver_open18/10.in");
    ofstream fout("lemonade.out");
    int N;
    int minimum = 0;
    int tbs_index = 0;
    fin >> N;
    int cows[N];
    int to_be_sorted[N];
    for (int i = 0; i < N; i++) {
        fin >> cows[i];
        if (cows[i] >= N - 1) { // # # # # 4; N = 5; 4 = N - 1
            cout << "Cow " << i << " (" << cows[i] << ") enters" << endl;
            minimum ++;
        } else {
            to_be_sorted[tbs_index ++] = cows[i];
        }
    }
    sort(to_be_sorted, to_be_sorted + N);
    int ahead = minimum;
    for (int i = 0; i < tbs_index; i++) {
        if (to_be_sorted[i] >= ahead) {
            ahead ++;
            minimum ++;
            cout << "Cow " << " (" << to_be_sorted[i] << ") enters" << endl;
        }
    }
    fout << minimum << endl;
}
