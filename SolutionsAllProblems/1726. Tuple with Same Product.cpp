// problem : https://leetcode.com/problems/tuple-with-same-product/description/
// submission : https://leetcode.com/problems/tuple-with-same-product/submissions/1534075305
// solution post : https://leetcode.com/problems/tuple-with-same-product/solutions/6386814/c-modern-readable-code-optimal-time-comp-zoed

// #include <limits>
// #include <vector>
// #include <unordered_map>

namespace Constants {
    auto constexpr SingleTupleCombinations{8};
}

// let 'n' be a length of the given array of numbers
// time complexity O(n^2)
// space complexity O(n^2)
// runtime 311 ms, beats 65.63 %
class Solution {
public:
    int tupleSameProduct(std::vector<int> const & nums) const {
        using namespace Constants;
        auto productsToCounts{std::unordered_map<size_t, size_t>{}};
        auto const numsSz{nums.size()};
        auto tuplesWithSameProductCount{0};
        auto end1{nums.end() - 1};
        auto end2{nums.end()};
        for(auto num1{nums.begin()}; num1 < end1; ++num1) {
            for(auto num2{num1 + 1}; num2 < end2; ++num2) {
                tuplesWithSameProductCount += productsToCounts[*num1 * *num2]++;  
            }
        } 
        return tuplesWithSameProductCount * SingleTupleCombinations;
    }
};
