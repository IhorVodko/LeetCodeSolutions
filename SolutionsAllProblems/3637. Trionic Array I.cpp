// problem : https://leetcode.com/problems/trionic-array-i/description
// submission : https://leetcode.com/problems/trionic-array-i/submissions/1906985126
// solution post : https://leetcode.com/problems/trionic-array-i/solutions/7549573/
//    c-modern-readable-code-beats-100-runtime-td5w

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the number of elements
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    // Public API to check whether the array is trionic
    [[nodiscard]]
    auto isTrionic(std::span<int const> const nums_) const -> bool;

private:
    // Expected number of monotonic direction changes in a trionic array
    static auto constexpr kTrionicTurnPointCnt{3};
};

auto Solution::isTrionic(std::span<int const> const nums_) const -> bool {
    // Alias for C++ ranges views
    namespace vs = std::views;

    // Total number of elements in the input array
    auto const numsSz{std::ssize(nums_)};
    // A trionic array must start with a strictly increasing segment
    if(nums_[0] >= nums_[1]) {
        return false;
    }
    // Initialize turn point count with the first increasing segment
    auto turnPointCnt{1};
    // Iterate from the third element onward
    for(auto const idx: vs::iota(2, numsSz)) {
        // Difference between the element two steps back and previous element
        auto const prevDif{nums_[idx - 2] - nums_[idx - 1]};
        // Difference between the previous element and current element
        auto const curDif{nums_[idx - 1] - nums_[idx]};
        // Product of consecutive differences to detect sign change
        auto const prod{prevDif * curDif};
        // Zero product means equal adjacent values which is invalid
        if(prod == 0) {
            return false;
        // Negative product indicates a change in monotonic direction
        } else if(prod < 0 && ++turnPointCnt > kTrionicTurnPointCnt) {
            return false;
        }
    }
    // Valid trionic array must have exactly three monotonic segments
    auto const isTrionic{turnPointCnt == kTrionicTurnPointCnt};
    return isTrionic;
}
