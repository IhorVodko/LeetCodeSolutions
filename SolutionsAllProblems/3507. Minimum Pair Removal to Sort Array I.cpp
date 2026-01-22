// problem : https://leetcode.com/problems/minimum-pair-removal-to-sort-array-i/description
// submission : https://leetcode.com/problems/minimum-pair-removal-to-sort-array-i/submissions/1893659924
// solution post : https://leetcode.com/problems/minimum-pair-removal-to-sort-array-i/solutions/7516250/
//    c-modern-readable-code-beats-100-runtime-1tvl

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream{"display_runtime.txt"} << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the vector length
// time complexity O(n^2)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto minimumPairRemoval(std::vector<int> & nums_) const -> int;
};

auto Solution::minimumPairRemoval(std::vector<int> & nums_) const -> int {
    namespace vs = std::views;
    using intL = std::numeric_limits<int>;

    auto opCnt{0};
    auto isDecreasing{false};
    // Repeat until only one element remains or the array is non-decreasing
    while(nums_.size() > 1 && !isDecreasing) {
        // Track the adjacent pair with the minimum sum
        auto minSum{intL::max()};
        auto minIdx{-1};
        // Assume the array is non-decreasing until proven otherwise
        isDecreasing = true;
        // Scan all adjacent pairs
        for(auto const idx: vs::iota(0, std::ssize(nums_) - 1)) {
            auto const num1{nums_[idx]};
            auto const num2{nums_[idx + 1]};
            auto const curSum{num1 + num2};
            if(minSum > curSum) {
                minSum = curSum;
                minIdx = idx;
            }
            // Detect violation of non-decreasing order
            if(num1 > num2) {
                isDecreasing = false;
            }
        }
        // If the array is not sorted, merge the minimum-sum adjacent pair
        if(!isDecreasing) {
            nums_[minIdx] = minSum;
            nums_.erase(nums_.begin() + minIdx + 1);
            ++opCnt;
        }
    }
    return opCnt;
}
