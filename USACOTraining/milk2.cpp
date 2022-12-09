/*
ID: william234
TASK: milk2
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct range
{
    int start, end;
};
bool compareInterval(range i1, range i2)
{
    return (i1.start < i2.start);
}
int main()
{
    ofstream fout("milk2.out");
    ifstream fin("milk2.in");
    int n;
    fin >> n;
    range ranges[n];
    for (auto i = 0; i < n; i++)
    {
        fin >> ranges[i].start >> ranges[i].end;
    }
    std::sort(ranges, ranges + n, compareInterval);
    int start = ranges[0].start, mostLasting = ranges[0].end;
    int maxLength = mostLasting - start, maxEmpty = 0;
    for (auto i = 1; i < n; i++)
    {
        if (ranges[i].start > mostLasting)
        {
            maxLength = max(maxLength, mostLasting - start);
            start = ranges[i].start;
            maxEmpty = max(maxEmpty, ranges[i].start - mostLasting);
        }
        mostLasting = max(mostLasting, ranges[i].end);
    }
    fout << maxLength << " " << maxEmpty << endl;
    return 0;
}