#include <string>
#include <vector>
#include <iostream>
using namespace std;
class Solution {
   public:
    int strStr(string haystack, string needle) {
        int n = haystack.size();
        int m = needle.size();
        if (n == 0 && m == 0) return 0;
        if (n < m) return -1;
        // Next (PMT)
        vector<int> next(m, 0);
        next[0] = -1;
        int i = 0, j = -1;
        cout << "Next: [-1";
        while (i < m - 1) {
            if (j == -1 || needle[i] == needle[j]) {
                i++, j++;
                next[i] = j;
                cout << ", " << next[i];
            } else {
                j = next[j];
            }
        }
        cout << "]\n";
        i = 0, j = 0;
        while (i < n) {
            if (j == -1 || haystack[i] == needle[j]) {
                i++, j++;
                if (j == m) return i - m;
            } else {
                j = next[j];
            }
        }
        return -1;
    }
};