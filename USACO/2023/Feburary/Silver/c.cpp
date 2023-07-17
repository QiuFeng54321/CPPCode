#include <iostream>
#include <map>
#include <unordered_set>
#include <vector>

struct f {
  size_t arrive_time;
  size_t arrive_airport;
};

class Flights {
public:
  void add_arrival(f flight, size_t start_time) {
    this->flights[start_time].push_back(flight);
  }

  // start time: flight
  std::map<size_t, std::vector<f>> flights;
};

class Travel {
public:
  void proc_airport(size_t airport, std::unordered_set<size_t> &updated) {
    size_t earliest = this->times[airport] + this->layovers[airport];
    Flights &flights = this->airports[airport];

    for (auto i = airport == 0 ? flights.flights.begin()
                               : flights.flights.lower_bound(earliest);
         i != flights.flights.end(); i = flights.flights.erase(i)) {
      // std::cout << "start time: " << i->first << std::endl;
      // if (airport != 0 and i->first < earliest) {
      //   break;
      // }
      for (auto j = i->second.cbegin(); j != i->second.cend(); j++) {
        // std::cout << "airport: " << j->arrive_airport
        //           << ", time: " << j->arrive_time << std::endl;
        if (this->times[j->arrive_airport] > j->arrive_time) {
          this->times[j->arrive_airport] = j->arrive_time;
          updated.insert(j->arrive_airport);
        }
      }
    }
  }

  void proc_all() {
    this->times[0] = 0;
    std::unordered_set<size_t> updated;
    updated.insert(0);
    while (!updated.empty()) {
      std::unordered_set<size_t> new_set;
      for (auto i = updated.cbegin(); i != updated.cend(); i++) {
        this->proc_airport(*i, new_set);
      }
      updated = new_set;
    }
  }

  void read_travel() {
    size_t airport_cnt, flights_cnt;
    std::cin >> airport_cnt >> flights_cnt;

    this->airports.resize(airport_cnt);
    this->layovers.resize(airport_cnt);
    this->times.resize(airport_cnt);

    for (size_t i = 0; i < flights_cnt; i++) {
      size_t start, start_time, arrive, arrive_time;
      std::cin >> start >> start_time >> arrive >> arrive_time;
      start -= 1;
      arrive -= 1;
      this->airports[start].add_arrival(
          f{
              .arrive_time = arrive_time,
              .arrive_airport = arrive,
          },
          start_time);
    }
    for (size_t i = 0; i < airport_cnt; i++) {
      std::cin >> this->layovers[i];
      this->times[i] = SIZE_MAX;
    }
  }

  void print_out() const {
    for (auto i = this->times.cbegin(); i != this->times.cend(); i++) {
      std::cout << (ssize_t)*i << std::endl;
    }
  }

  std::vector<Flights> airports;
  std::vector<size_t> layovers;
  std::vector<size_t> times;
};

int main() {
  Travel travel;
  travel.read_travel();
  travel.proc_all();
  travel.print_out();
  return 0;
}
