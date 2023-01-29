/*
ID: william234
TASK: ${ProgramName}
LANG: C++
*/
#define PROGRAM_NAME "${ProgramName}"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <vector>

#pragma region States
#define DEBUG 0
#define USE_FILE 0
#define MOD 1000000007
#define USE_DSU 0
#pragma endregion

#pragma region Definitions
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#endif
#define FAST_IO                  \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);
#if USE_FILE
#define MAIN_FILE_HEADER                       \
    freopen(PROGRAM_NAME ".in", "r", stdin);   \
    freopen(PROGRAM_NAME ".out", "w", stdout); \
    FAST_IO
#else
#define MAIN_FILE_HEADER FAST_IO
#endif
#if DEBUG
#define ifdbg(stmt) stmt;
#define dbg(stmt) cout << stmt;
#define dbgl(stmt) cout << stmt << endl;
#else
#define ifdbg(stmt)
#define dbg(stmt)
#define dbgl(stmt)
#endif
#define dbgs if (DEBUG)
#define ff first
#define ss second
#define car const auto&
#define ctr(t) const t&
#define var auto
#define all(x) x.begin(), x.end()
#define f0r(i, n) for (int i = 0; i < n; i++)
#define f0ri(i, n) for (int i = 0; i <= n; i++)
#define f1r(i, n) for (int i = 1; i < n; i++)
#define f1ri(i, n) for (int i = 1; i <= n; i++)
using namespace std;
using str = string;
using ll = long long;
template <typename T>
T last_true(T lo, T hi, function<bool(T)> f) {
    // if none of the values in the range work, return lo - 1
    lo--;
    while (lo < hi) {
        // find the middle of the current range (rounding up)
        T mid = lo + (hi - lo + 1) / 2;
        if (f(mid)) {
            // if mid works, then all numbers smaller than mid also work
            lo = mid;
        } else {
            // if mid does not work, greater values would not work either
            hi = mid - 1;
        }
    }
    return lo;
}
template <typename T>
T first_true(T lo, T hi, function<bool(T)> f) {
    hi++;
    while (lo < hi) {
        T mid = lo + (hi - lo) / 2;
        if (f(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return lo;
}
// Int div a / b with negative result gives upper bound so this is the fix.
ll floorDiv(ll a, ll b) {
    ll val = a / b;
    while (val * b > a) val--;
    return val;
}
#if USE_DSU
struct DSU {
    vector<int> e;
    DSU(int N) { e = vector<int>(N, -1); }

    // get representive component (uses path compression)
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }

    bool same_set(int a, int b) { return get(a) == get(b); }

    int size(int x) { return -e[get(x)]; }

    bool unite(int x, int y) {  // union by size
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return true;
    }
};
#endif
#pragma endregion

char to_ascii(char a) { return a + 'a'; }
char to_repr(char c) { return c - 'a'; }

int dx[]{0, 1, 0, -1, 1, 1, -1, -1};
int dy[]{1, 0, -1, 0, 1, -1, 1, -1};

struct Node {
    Node* children[26];
    bool hasWord = false;
    bool isNo = false;
};

Node* rootNode = new Node;
map<Node*, bool> visited;

void add_word(str s, bool isNo) {
    var curNode = rootNode;
    for (car c : s) {
        int i = to_repr(c);
        if (!curNode->children[i]) {
            curNode->children[i] = new Node;
        }
        curNode = curNode->children[i];
    }
    curNode->hasWord = true;
    curNode->isNo = isNo;
}

// 1 - 26: a - z, 0: none
int w, h;
int geneCount;
const int MaxWordLen = 100;
int wordCount;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution randInt;
uniform_real_distribution randReal(0., 1.);
uniform_int_distribution<char> randChar(0, 25);

struct Unit {
    char* genes;
    int finalized_fitness = INT_MIN;
    int age = 0;
    Unit() { genes = new char[geneCount]; }
    char& get(int x, int y) {
        int idx = y * h + x;
        if (!(0 <= idx && idx < geneCount)) {
            throw runtime_error("("s + to_string(x) + ", " + to_string(y));
        }
        return genes[idx];
    }
    char& operator()(int x, int y) { return get(x, y); }
    void randomise() {
        f0r(i, geneCount) { genes[i] = randChar(gen); }
    }
    Unit mate(ctr(Unit) other) {
        int crosspoint = randInt(gen);
        Unit newUnit{};
        memcpy(newUnit.genes, genes, crosspoint);
        memcpy(newUnit.genes + crosspoint, other.genes + crosspoint,
               geneCount - crosspoint);
        f0r(i, geneCount) {
            if (randReal(gen) < 0.06) {
                newUnit.genes[i] = randChar(gen);
            }
        }
        return newUnit;
    }
    int recur(int x, int y, int di, Node* cur) {
        if (!cur) return 0;
        int res = 0;
        if (cur->hasWord) {
            if (!visited[cur]) {
                res += cur->isNo ? -3 : 1;
                visited[cur] = true;
            } else {
                res --;
            }
        }
        int nx = x + dx[di];
        int ny = y + dy[di];
        if (nx < 0 || nx >= w || ny < 0 || ny >= h) return res;
        return res + recur(nx, ny, di, cur->children[get(nx, ny)]);
    }
    int fitness() {
        visited.clear();
        int res = 0;
        f0r(i, w) {
            f0r(j, h) {
                f0r(di, 8) {
                    res += recur(i, j, di, rootNode->children[get(i, j)]);
                }
            }
        }
        finalized_fitness = res;
        return res;
    }
    bool operator>(const Unit& another) const {
        return finalized_fitness > another.finalized_fitness;
    }
    friend ostream& operator<<(ostream& os, Unit& unit) {
        f0r(i, w) {
            f0r(j, h) { os << to_ascii(unit(i, j)); }
            os << "\n";
        }
        os << "fitness = " << unit.finalized_fitness << ", age = " << unit.age;
        return os;
    }
};
bool cmpAge(const Unit& a, const Unit& b) { return a.age > b.age; }

const int PopulationSize = 2000;
const int RandSize = 10;
// const int RandSize = 0;
const int LeaveElite = 1;
const bool SelectRandom = 0;
const int OffspringSize = SelectRandom ? PopulationSize - LeaveElite : ((PopulationSize - LeaveElite) / 2 - 1);
class GA {
   public:
    Unit population[PopulationSize];
    discrete_distribution<int> weightedRand;
    int min_fitness = INT_MAX;
    set<int> selected{};
    GA() {
        for (Unit& unit : population) {
            unit.randomise();
            unit.fitness();
            min_fitness = min(min_fitness, unit.finalized_fitness);
        }
        sort(population, population + PopulationSize, greater<Unit>());
    }
    pair<int, int> selectNonRepetitive() {
        int i;
        while (selected.count(i = weightedRand(gen))) {
            // cout << i << endl;
        }
        selected.insert(i);
        int j;
        while (selected.count(j = weightedRand(gen))) {
        }
        selected.insert(j);
        return {i, j};
    }
    pair<int, int> selectRandom() {
        int i = weightedRand(gen);
        int j = weightedRand(gen);
        return {i, j};
    }
    void round() {
        vector<int> weights{};
        selected.clear();
        for (Unit& unit : population) {
            weights.push_back(unit.finalized_fitness + min_fitness + 4);
            unit.age++;
        }
        weightedRand =
            discrete_distribution<int>(weights.begin(), weights.end());
        min_fitness = INT_MAX;
        Unit offsprings[OffspringSize];
        for (Unit& offspring : offsprings) {
            var[i, j] = SelectRandom ? selectRandom() : selectNonRepetitive();
            offspring = population[i].mate(population[j]);
            offspring.fitness();
            min_fitness = min(min_fitness, offspring.finalized_fitness);
        }
        for (int i = 0; i < OffspringSize; i++) {
            population[PopulationSize - i - 1] = offsprings[i];
        }
        sort(population, population + PopulationSize, cmpAge);
        for (int i = 0; i < RandSize; i++) {
            Unit& randUnit = population[i + LeaveElite];
            randUnit.randomise();
            randUnit.fitness();
            min_fitness = min(min_fitness, randUnit.finalized_fitness);
        }
        sort(population, population + PopulationSize, greater<Unit>());
    }
};

/*
3 3 5
+ ale
+ oat
+ zed
+ old
+ zoo



5 3 7
+ echo
+ baker
+ apt
+ toe
+ ore
+ eat
+ cap

9 7 16
+ halloween
+ challenge
+ almanac
+ choice
+ campus
+ deadpan
+ gender
+ announced
+ airline
+ irishman
+ inane
+ mound
+ lope
+ cane
+ area
+ lode
*/

void solve() {
    GA ga;
    int round = 1;
    cout << "Start\n";
    bool autoRound = false;
    while (true) {
        if (!autoRound) {
            str s;
            getline(cin, s);
            if (s == "q") break;
            if (s == "a") {
                autoRound = true;
            }
        }
        ga.round();
        cout << "Round " << round++ << endl;
        if (ga.population[0].finalized_fitness >= wordCount) {
            cout << "Solution found: \n";
            cout << ga.population[0] << endl;
            break;
        }
        cout << "Top 3 units:\n";
        f0r(i, 3) {
            cout << i << ": \n";
            cout << ga.population[i] << endl;
        }
    }
}
void test() {
    Unit unit;
    unit.randomise();
    while (unit.fitness() < 2) {
        unit.randomise();
    }
    cout << unit << endl;
}

int main() {
    MAIN_FILE_HEADER
    cin >> w >> h;
    geneCount = w * h;
    randInt = uniform_int_distribution(0, geneCount);
    cin >> wordCount;
    f0r(i, wordCount) {
        char state;
        str s;
        cin >> state >> s;
        add_word(s, state == '-');
    }
    solve();
    return 0;
}