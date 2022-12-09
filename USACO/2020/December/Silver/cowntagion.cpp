/*
ID: william234
TASK: test
LANG: C++
*/
/* LANG can be C++11 or C++14 for those more recent releases */
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>

#define DEBUG 0
#define rin (DEBUG ? fin : cin)
#define rout (DEBUG ? fout : cout)
#define IFDEBUG(stmt) if (DEBUG) {stmt;}

using namespace std;
int N;
vector<int> adjMap[100000];
int population[100000];
queue<int> path;
int days = 0;

int main()
{
#ifdef DEBUG
    ofstream fout ("cowntagion.out");
    ifstream fin ("cowntagion.in");
#endif

    rin >> N;
    for (int i = 0; i < N - 1; i++)
    {
        int f, t;
        rin >> f >> t;
        adjMap[f - 1].push_back(t - 1);
        adjMap[t - 1].push_back(f - 1);
    }
    int start = 0;
    // for (int i = 0; i < N; i++) {
    //     if (adjMap[i].size() > adjMap[start].size())
    //         start = i;
    // }
    path.push(start);
    population[start] = 1;
    while (path.size() != 0) {
        auto size = path.size();
        for (int _ = 0; _ < size; _ ++) {
            auto index = path.front();
            path.pop();
            auto childrenCount = 0;
            auto parentPop = population[index];
            for (auto child : adjMap[index]) {
                if (population[child] == 0) {
                    days ++;
                    childrenCount ++;
                    population[child] ++;
                    population[index] --;
                    path.push(child);
                    IFDEBUG(cout << "Spread to " << child << endl)
                }
            }
            while (parentPop < childrenCount + 1) {
                parentPop *= 2;
                days ++;
                IFDEBUG(cout << "Double " << index << endl)
            }
            population[index] = parentPop - childrenCount;
        }
    }
    rout << days << endl;
    return 0;
}