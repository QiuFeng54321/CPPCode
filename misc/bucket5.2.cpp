#include <iostream>

using namespace std;

int main() {
	int N;
	cin >> N;
	int capacities[N], storage[N];
	for (int i = 0; i < N; i ++)
		cin >> capacities[N];
	for (int i = 0; i < N; i ++)
		cin >> storage[N];
	for (int i = 0; i < N - 1; i ++) {
		// Branch storage not fulfilled
        if (storage[i + 1] == capacities[i + 1]) continue;
		if (storage[i + 1] + storage[i] > capacities[i + 1]) {
			int pour = capacities[i + 1] - storage[i + 1];
			storage[i + 1] = capacities [i + 1];
			storage[i] = pour;
		} else {
			storage[i + 1] += storage[i];
			storage[i] = 0;
		}
	}
	for (int i = 0; i < N; i++) {
		cout << storage[i] << " ";
	}
}