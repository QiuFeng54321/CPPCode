#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& A) {
        vector<vector<int>> transposed{};
        if(A.size() == 0) {
            return transposed;
        }
        int x = A.size();
        int y = A[0].size();
        for (int i = 0; i < y; i++) {
            transposed.push_back(vector<int>());
            for (int j = 0; j < x; j++) {
                transposed[i].push_back(A[j][i]);
            }
        }
        return transposed;
    }
};


