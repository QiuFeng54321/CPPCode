/*
ID: william234
TASK: palsquare
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string to_base(int i, int b)
{
    string str = "";
    int q = i, r = 0;
    while (q != 0)
    {
        r = q % b;
        q = q / b;
        str.insert(str.begin(), r < 10 ? r + '0' : r - 10 + 'A');
    }
    return str;
}
bool is_palindrome(string str)
{
    int head = 0, tail = str.size() - 1;
    while (head <= tail)
    {
        if (str[head] != str[tail])
            break;
        head++;
        tail--;
    }
    return head > tail;
}

int main()
{
    ofstream fout("palsquare.out");
    ifstream fin("palsquare.in");
    int b;
    fin >> b;
    for (auto n = 1; n <= 300; n++)
    {
        auto n_str = to_base(n, b);
        auto squared = n * n;
        auto squared_str = to_base(squared, b);
        if (is_palindrome(squared_str))
            fout << n_str << ' ' << squared_str << endl;
    }
    return 0;
}