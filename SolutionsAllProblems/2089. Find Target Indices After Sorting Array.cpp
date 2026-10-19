// problem : https://leetcode.com/problems/find-target-indices-after-sorting-array/description
// submission : https://leetcode.com/problems/find-target-indices-after-sorting-array/submissions/2176215689
// solution post : https://leetcode.com/problems/find-target-indices-after-sorting-array/solutions/8579522/
//  simplanation-simple-explanation-by-cyber-r99j

// Approach : Linear Counting over Sorting
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the total count of numbers
// Time :  O(n)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <vector>

namespace rs = std::ranges;
namespace vs = std::views;

namespace {

// Tracks counts of elements strictly less than and equal to the target.
struct CountState final {
    int mLessmTargetNumCnt{};
    int mTargetNumCnt{};
};

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace 

class Solution final {
public:
    [[nodiscard]]
    static auto targetIndices(
        std::vector<int> & nums_,
        int const targetNum_
    ) -> std::vector<int>;
};

auto Solution::targetIndices(
    std::vector<int> & nums_,
    int const targetNum_
) -> std::vector<int> {
    // 1. Define accumulation logic to compute required element counts.
    auto const accumCountState{[targetNum_] (
        CountState const cntState_,
        int const num_
    ) -> CountState {
        auto const [lessTrgtNumCnt, trgtNumCnt]{cntState_};

        if(num_ < targetNum_) {
            return {lessTrgtNumCnt + 1, trgtNumCnt};
        } else if(num_ == targetNum_) {
            return {lessTrgtNumCnt, trgtNumCnt + 1};
        }

        return cntState_;
    }};

    // 2. Traverse the array once to calculate target and smaller element counts.
    auto const [lessTrgtNumCnt, trgtNumCnt]{
        rs::fold_left(nums_, CountState{}, accumCountState)
    }; 

    // 3. Generate the sequence of target indices using the computed counts.
    return rs::to<std::vector>(vs::iota(lessTrgtNumCnt, lessTrgtNumCnt + trgtNumCnt));
}
