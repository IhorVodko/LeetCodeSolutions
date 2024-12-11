// problem : https://leetcode.com/problems/array-partition/description/
// submission : https://leetcode.com/problems/array-partition/submissions/1476482586
// solution post : https://leetcode.com/problems/array-partition/solutions/6137361/c-modern-readable-code-beats-100-runtime


// #include <algorithm>
// #include <array>


class Solution {
public:
    // let 'n' be a 'nums' array length
    // 'm' - a maximum allowed number in 'nums'
    // time complexity O(n + m)
    // space complexity O(m)
    // runtime 0 ms, beats 100.00 %
    int arrayPairSum(
        std::vector<int> const & nums
    ) const {
        sort(nums);
        return findMaxSum();
    }
private:
    void sort(
        auto const & nums 
    ) const {
        std::fill(count.begin(), count.end(), 0);
        for(auto const num: nums) {
            ++count.at(num + maxNum);
        }
    }
    int findMaxSum() const {
        auto sum{0};
        auto isEvenIdx{true};
        for(auto num{0}; num < countSize; ++num) {
            while(count.at(num)-- > 0) {
                sum += isEvenIdx ? num - maxNum : 0;
                isEvenIdx = !isEvenIdx;
            }
        }
        return sum;
    }
    int static constexpr maxNum{10'000};
    int static constexpr countSize{maxNum * 2 + 1};
    std::array<size_t, countSize> static count;
};

std::array<size_t, Solution::countSize> Solution::count{};
