// problem : https://leetcode.com/problems/find-the-largest-almost-missing-integer/description
// submission : https://leetcode.com/problems/find-the-largest-almost-missing-integer/submissions/2111882193
// solution post : https://leetcode.com/problems/find-the-largest-almost-missing-integer/solutions/8468942/
//    simplanation-simple-explanation-by-cyber-1zqx

// Approach : Window Overlap Classification
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the count of numbers
// 'm' - maximum possible number
// Time :  O(n + m)
// Space : O(m), auxiliary

// import std;

// #include <algorithm>
// #include <array>
// #include <iterator>
// #include <ranges>
// #include <vector>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

// Limits based on constraints and failure states mapping
constexpr auto kNoSolution{-1};
constexpr auto kMinWindowSz{1};
constexpr auto kUniqueNumCnt{1};
constexpr auto kMaxNum{51};

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

class Solution final{
public:
    [[nodiscard]]
    static auto largestInteger(
        std::vector<int> const & nums_,
        int const windowSz_
    ) -> int;
};

auto Solution::largestInteger(
    std::vector<int> const & nums_,
    int const windowSz_
) -> int {
    // 1. Return max array element when the single window spans the entire array
    if(windowSz_ == nums_.size()) {
        return rs::max(nums_);
    }

    // 2. Tally overall element frequencies to identify unique elements
    auto cntPerNum{std::array<int, kMaxNum>{}};
    for(auto const num: nums_) {
        ++cntPerNum[num];
    }
    
    // 3. Return the max globally unique element when window size is minimal
    if(windowSz_ == kMinWindowSz) {
        // Locates the largest unique value by searching frequencies backwards
        auto const rng{rs::find_last(cntPerNum, kUniqueNumCnt)};
        auto const num{static_cast<int>(std::distance(cntPerNum.begin(), rng.begin()))};

        return num == kMaxNum ? kNoSolution : num;
    }
        
    // 4. Return max unique boundary element, as inner items span multiple windows
    return std::max(
        cntPerNum[nums_.front()] == kUniqueNumCnt ? nums_.front() : kNoSolution,
        cntPerNum[nums_.back()] == kUniqueNumCnt ? nums_.back() : kNoSolution
    );
}
