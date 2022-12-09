/*
ID: william234
TASK: transform
LANG: C++                 
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
bool impossibleTransformation[9];

int main() {
    ofstream fout ("transform.out");
    ifstream fin ("transform.in");
    int n;
    fin >> n;
    bool matrixOrigin[n][n], matrixTarget[n][n];
    std::string row;
    for (auto i = 0; i < n; i++) {
        fin >> row;
        for (auto j = 0; j < n; j++) {
            matrixOrigin[i][j] = row[j] == '@';
        }
    }
    for (auto i = 0; i < n; i++) {
        fin >> row;
        for (auto j = 0; j < n; j++) {
            matrixTarget[i][j] = row[j] == '@';
        }
    }
    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            if (matrixOrigin[n - j - 1][i] != matrixTarget[i][j]) impossibleTransformation[0] = true;
            if (matrixOrigin[n - i - 1][n - j - 1] != matrixTarget[i][j]) impossibleTransformation[1] = true;
            if (matrixOrigin[j][n - i - 1] != matrixTarget[i][j]) impossibleTransformation[2] = true;
            if (matrixOrigin[i][n - j - 1] != matrixTarget[i][j]) impossibleTransformation[3] = true;
            if (matrixOrigin[n - j - 1][n - i - 1] != matrixTarget[i][j]) impossibleTransformation[4] = true;
            if (matrixOrigin[n - i - 1][j] != matrixTarget[i][j]) impossibleTransformation[5] = true;
            if (matrixOrigin[j][i] != matrixTarget[i][j]) impossibleTransformation[6] = true;
            if (matrixOrigin[i][j] != matrixTarget[i][j]) impossibleTransformation[7] = true;
        }
    }
    for (auto i = 0; i < sizeof(impossibleTransformation); i++) {
        if (!impossibleTransformation[i]) {
            cout << i << endl;
            auto value = i;
            if (4 <= i && i <= 6) value = 4;
            if (value > 6) value -= 2;
            cout << value + 1 << endl;
            fout << value + 1 << endl;
            break;
        }
    }
    return 0;
}