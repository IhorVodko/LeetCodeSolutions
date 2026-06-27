// problem : https://leetcode.com/problems/find-the-maximum-number-of-elements-in-subset/description
// submission : https://leetcode.com/problems/find-the-maximum-number-of-elements-in-subset/submissions/2047701893
// solution post : https://leetcode.com/problems/find-the-maximum-number-of-elements-in-subset/solutions/8361247/
//    modern-readable-code-optimal-time-comple-4tg6

// Approach : Hash Map Frequency Counting with Sequence Tracing
// Runtime : 50 ms, beats 89.14 %

// Complexity
// let 'n' be the count of numbers
// 'm' - maximum number
// Time :  O(n * log(log(m)))
// Space : O(n)

// import std;

#define NDEBUG

#include <cassert>

class Solution final {
public:
    [[nodiscard]]
    static auto maximumLength(std::vector<int> const & nums_) -> int;
};

auto Solution::maximumLength(std::vector<int> const & nums_) -> int {
    namespace vs = std::views;
    namespace rs = std::ranges;

    auto numToCnt{std::unordered_map<long long, int>{}};
    numToCnt.reserve(nums_.size());
    rs::for_each(nums_, [&] (auto const num_) { ++numToCnt[num_]; });

    // 1 is a special case requiring an odd frequency count.
    auto maxLen{
        numToCnt.contains(1) ? (numToCnt[1] - (numToCnt[1] % 2 == 0 ? 1 : 0)) : 1
    };

    // Early return if the array contains only one unique number 1.
    if(maxLen > 0 && numToCnt.size() == 1) {
        return maxLen;
    }

    // Trace the squaring sequence as long as pairs exist.
    auto const CalcLen{[&] (auto num_) {
        auto len{0};
        while(numToCnt.contains(num_) && numToCnt[num_] >= 2) {
            len += 2;
            num_ *= num_; 
        }

        // Add the peak element, or backtrack if missing.
        return len + (numToCnt.contains(num_) ? 1 : -1);
    }};
    
    auto lens{
        numToCnt |
        vs::keys |
        vs::filter([] (auto const num_) { return num_ > 1; }) |
        vs::transform(CalcLen)
    };

    assert(!rs::empty(lens));

    return std::max(maxLen, rs::max(lens));
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
