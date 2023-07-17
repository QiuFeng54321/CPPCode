#include <iostream>
#include <map>
#include <unordered_set>
#include <vector>

#define DEBUG 0

#define dbgs if (DEBUG)
using namespace std;
using str = string;
using ll = long long;

struct flight {
    size_t a;
    size_t p;
};

class flights {
   public:
    void add_arrival(flight flight, size_t start_time) {
        flights[start_time].push_back(flight);
    }
    map<size_t, vector<flight>> flights;
};

class Travel {
   public:
    void proc_airport(size_t airport, unordered_set<size_t> &updated) {
        size_t earliest = times[airport] + layovers[airport];
        flights &flights = airports[airport];

        for (auto i = airport == 0 ? flights.flights.begin()
                                   : flights.flights.lower_bound(earliest);
             i != flights.flights.end(); i = flights.flights.erase(i)) {
            for (auto j = i->second.cbegin(); j != i->second.cend(); j++) {
                if (times[j->p] > j->a) {
                    times[j->p] = j->a;
                    updated.insert(j->p);
                }
            }
        }
    }

    void proc_all() {
        times[0] = 0;
        unordered_set<size_t> updated;
        updated.insert(0);
        while (!updated.empty()) {
            unordered_set<size_t> new_set;
            for (auto i = updated.cbegin(); i != updated.cend(); i++) {
                proc_airport(*i, new_set);
            }
            updated = new_set;
        }
    }

    void read_travel() {
        size_t airport_cnt, flights_cnt;
        cin >> airport_cnt >> flights_cnt;

        airports.resize(airport_cnt);
        layovers.resize(airport_cnt);
        times.resize(airport_cnt);

        for (size_t i = 0; i < flights_cnt; i++) {
            size_t start, start_time, arrive, a;
            cin >> start >> start_time >> arrive >> a;
            start -= 1;
            arrive -= 1;
            airports[start].add_arrival(
                flight{a, arrive},
                start_time);
        }
        for (size_t i = 0; i < airport_cnt; i++) {
            cin >> layovers[i];
            times[i] = SIZE_MAX;
        }
    }

    void print_out() const {
        for (auto i = times.cbegin(); i != times.cend(); i++) {
            cout << (ssize_t)*i << endl;
        }
    }

    vector<flights> airports;
    vector<size_t> layovers;
    vector<size_t> times;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    dbgs {
        freopen("a.in", "r", stdin);
        freopen("a.out", "w", stdout);
    }
    Travel travel;
    travel.read_travel();
    travel.proc_all();
    travel.print_out();
    return 0;
}
