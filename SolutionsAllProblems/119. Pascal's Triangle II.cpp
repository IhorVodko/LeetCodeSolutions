// problem : https://leetcode.com/problems/pascals-triangle-ii/description/
// submission : https://leetcode.com/problems/pascals-triangle-ii/submissions/1477938872
// solution post : https://leetcode.com/problems/pascals-triangle-ii/solutions/6143478/c-modern-readable-code-beats-100-runtime-z9uk


// #include <vector>


class Solution {
public:
    // let 'n' be a parameter 'rowIndex' 
    // time complexity O(n^2)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    std::vector<int> getRow(int rowIndex) const {
        if(rowIndex == 0) {
            return {1};
        }
        auto result{std::vector<int>{1}};
        result.reserve(rowIndex);
        while(rowIndex-- > 0) {
            for(auto num{result.rbegin()}, end{result.rend() - 1}; num < end;
                ++num
            ) {
                *num += *(num + 1);
            }
            result.emplace_back(1); 
        }
        return result; 
    }
};
