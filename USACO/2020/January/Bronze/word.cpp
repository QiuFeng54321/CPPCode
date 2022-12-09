#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
    ifstream fin("word.in");
    ofstream fout("word.out");
    std::string res = "";
    int N, lim;
    int cur_word_count = 0;
    fin >> N >> lim;
    for (int i = 0; i < N; i++) {
        std::string word;
        fin >> word;
        int len = word.length();
        if (cur_word_count + len > lim) {
            res += "\n";
            cur_word_count = 0;
        }
        if (cur_word_count != 0) res += " ";
        res += word;
        cur_word_count += len;
    }
    fout << res << endl;
}