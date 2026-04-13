// problem : https://leetcode.com/problems/minimum-distance-to-the-target-element/description
// submission : https://leetcode.com/problems/minimum-distance-to-the-target-element/submissions/1977268484
// solution post : https://leetcode.com/problems/minimum-distance-to-the-target-element/solutions/7891313/
//    c-modern-readable-code-beats-100-runtime-wz22

// Approach : Bidirectional Outward Search
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the array length
// complexity :  O(n)
// complexity : O(1)

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

class Solution final {
public:

    [[nodiscard]]
    auto getMinDistance(
        std::vector<int> const & nums_,
        int const targetNum_,
        int const startIdx_
    ) const -> int;
};

auto Solution::getMinDistance(
    std::vector<int> const & nums_,
    int const targetNum_,
    int const startIdx_
) const -> int {
    namespace vs = std::views;

    using intLim = std::numeric_limits<int>;

    auto numsSz{std::ssize(nums_)};

    for(auto const dist: vs::iota(0, std::ssize(nums_))) {
        if( auto const l{startIdx_ - dist}, r{startIdx_ + dist}; 
            (l >= 0 && nums_[l] == targetNum_) ||
            (r < numsSz && nums_[r] == targetNum_)
        ) {
            return dist;
        }
    }

    return -1;
}
