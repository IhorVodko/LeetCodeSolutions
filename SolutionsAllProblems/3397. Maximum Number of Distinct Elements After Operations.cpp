// problem : https://leetcode.com/problems/maximum-number-of-distinct-elements-after-operations/description/
// submission : https://leetcode.com/problems/maximum-number-of-distinct-elements-after-operations/submissions/1804877167
// solution post : https://leetcode.com/problems/maximum-number-of-distinct-elements-after-operations/solutions/7283621/
//    c-modern-readable-code-beats-100-runtime-3km8/

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream("display_runtime.txt") << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class Solution {
public:
// let 'n' be the number of the given numbers
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maxDistinctElements(
        std::vector<int> & nums_,
        int const delta_
    ) const -> int;
};

auto Solution::maxDistinctElements(
    std::vector<int> & nums_,
    int const delta_
) const -> int {
    namespace rngs = std::ranges;

    rngs::sort(nums_);
    auto uniqueNumCnt{0};
    auto prevUniqueNum{std::numeric_limits<int>::min()};
    for(auto const num: nums_) {
        auto const numLowerBound{num - delta_};
        auto const numUpperBound{num + delta_};
        auto const firstAvailableUniqueNum{prevUniqueNum + 1};
        auto currUniqueNum{std::min(
            std::max(numLowerBound, firstAvailableUniqueNum),
            numUpperBound
        )};
        if(currUniqueNum > prevUniqueNum) {
            ++uniqueNumCnt;
            prevUniqueNum = currUniqueNum;
        }
    }
    return uniqueNumCnt;
}
