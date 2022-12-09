/*
ID: william234
TASK: dualpal
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
    ofstream fout("dualpal.out");
    ifstream fin("dualpal.in");
    int n, s;
    fin >> n >> s;
    s++;
    for (auto i = 0; i < n; )
    {
        int base_count = 0;
        for (auto b = 2; b <= 10; b++)
        {
            auto str = to_base(s, b);
            if (is_palindrome(str))
            {
                base_count ++;
                if (base_count == 2) break;
            }
        }
        if (base_count == 2) {
            fout << s << endl;
            i ++;
        }
        s++;
    }
    return 0;
}