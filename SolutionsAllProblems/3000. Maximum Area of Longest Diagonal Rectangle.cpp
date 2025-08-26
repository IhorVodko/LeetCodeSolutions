// problem : https://leetcode.com/problems/maximum-area-of-longest-diagonal-rectangle/description
// submission : https://leetcode.com/problems/maximum-area-of-longest-diagonal-rectangle/submissions/1749110478
// solution post : https://leetcode.com/problems/maximum-area-of-longest-diagonal-rectangle/solutions/7124884/
//    c-modern-readable-code-beats-100-runtime-ju41

// #include <algorithm>
// #include <cmath>
// #include <vector>

class Solution {
public:
// let 'n' be a count of the given dimension pairs
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    int areaOfMaxDiagonal(vector<vector<int>> const & dims_) const;
};

int Solution::areaOfMaxDiagonal(vector<vector<int>> const & dims_) const {
    auto maxDiagonal{-1.0};
    auto maxArea{-1};
    for(auto const dim: dims_) {
        auto const width{dim.at(0)};
        auto const length{dim.at(1)};
        auto const currDiagonal{std::sqrt(length * length + width * width)};
        if(currDiagonal < maxDiagonal) {
            continue;
        }
        auto const currArea{width * length};
        maxArea = currDiagonal == maxDiagonal ?
            std::max(maxArea, currArea) :
            currArea;
        maxDiagonal = currDiagonal;
    } 
    return maxArea;
}
