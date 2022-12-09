#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    int getWinner(vector<int>& arr, int k) {
        int latest_win = 0;
        int latest_win_freq = 0;
        int index = 0;
        int comp_index = 1;
        int arr_size = arr.size();
        auto data = arr.data();
        while (true) {
            int win = 0;
            if (data[index] > data[comp_index]) {
                win = data[index];
            } else { // No condition such that arr[0] == arr[1] can be true
                win = data[comp_index];
                index = comp_index;
            }
            comp_index ++;
            if (win != latest_win) {
                latest_win = win;
                latest_win_freq = 1;
            } else {
                latest_win_freq ++;
            }
            if (latest_win_freq == k) return latest_win;
            if (latest_win_freq > arr_size) return latest_win;
            if (comp_index >= arr_size) comp_index = 0;
        }
    }
};