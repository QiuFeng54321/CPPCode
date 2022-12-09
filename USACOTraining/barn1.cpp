/*
ID: william234
TASK: barn1
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <algorithm>
#include <assert.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
int lengths[205]{0};
bool occupied[205]{0};
struct Separate
{
    int index, sep;
};
Separate seps[205]{0};
bool compareSeparate(Separate s1, Separate s2)
{
    return s1.sep < s2.sep;
}
bool compareSeparateIndex(Separate s1, Separate s2)
{
    return s1.index < s2.index;
}

int main()
{
    ofstream fout("barn1.out");
    ifstream fin("barn1.in");
    int maxBoards, stalls, cows;
    fin >> maxBoards >> stalls >> cows;
    for (int i = 0; i < cows; i++)
    {
        int index;
        fin >> index;
        occupied[index - 1] = true;
    }
    for (int i = 0; i < stalls; i++)
    {
        cout << (occupied[i] ? 'x' : '_');
    }
    cout << endl;
    int currentSepsIndex = -1;
    for (int i = 1; i < stalls; i++)
    {
        if (occupied[i - 1] && !occupied[i])
        {
            currentSepsIndex++;
            seps[currentSepsIndex].index = i;
        }
        if (!occupied[i])
            seps[currentSepsIndex].sep++;
    }
    if (!occupied[stalls - 1])
        currentSepsIndex--;
    sort(seps, seps + currentSepsIndex + 1, compareSeparate);
    for (int i = 0; i < currentSepsIndex + 1; i++)
    {
        cout << "S" << seps[i].index << " + " << seps[i].sep << endl;
    }
    for (int i = 0; i < max(currentSepsIndex + 2 - maxBoards, 0); i++)
    {
        assert(i <= currentSepsIndex);
        for (int j = 0; j < seps[i].sep; j++)
        {
            assert(seps[i].index + j < stalls);
            occupied[seps[i].index + j] = true;
            // cout << "D" << seps[i].index + j << endl;
        }
    }
    // cout << "Done" << endl;
    for (int i = 0; i < stalls; i++)
    {
        assert(i < stalls);
        cout << (occupied[i] ? 'x' : '_');
    }
    // cout << "Getting length" << endl;
    int lengthIndex;
    for (int i = 0; i < stalls; i++)
    {
        assert(lengthIndex < 205);
        if (i != 0)
        {
            if (!occupied[i] && occupied[i - 1])
            {
                lengthIndex++;
            }
        }
        if (occupied[i])
            lengths[lengthIndex]++;
    }
    if (occupied[stalls - 1])
        lengthIndex++;
    // cout << "Lengths done" << endl;
    int total = 0;
    for (int i = 0; i < lengthIndex; i++)
    {
        cout << lengths[i] << endl;
        total += lengths[i];
    }
    fout << total << endl;
    return 0;
}