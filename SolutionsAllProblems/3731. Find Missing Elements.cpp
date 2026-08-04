// problem : https://leetcode.com/problems/find-missing-elements/description/
// submission : https://leetcode.com/problems/find-missing-elements/submissions/2094288844
// solution post : https://leetcode.com/problems/find-missing-elements/solutions/8441179/simplanation-simple-explanation-by-cyber-lsm9

// Approach : Direct Addressing (Bit Array) Hashing
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the number of elements in the array
// 'm' - the difference between the maximum and minimum elements
// Time :  O(n + m)
// Space : O(1), auxiliary space

// import std;


namespace  {

namespace rs = std::ranges;
namespace vs = std::views;

auto constexpr kMaxNum{100uz};

using numsT = std::vector<int>;

// Initializer to configure fast I/O before main() runs
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
    static auto findMissingElements(numsT const & nums_) -> numsT;
};

auto Solution::findMissingElements(numsT const & nums_) -> numsT {
    // Track presence of each input number to identify gaps
    auto numsMask{std::bitset<kMaxNum + 1uz>{}};
    for(auto const num: nums_) {
        numsMask.set(num);
    }

    auto const [minNum, maxNum]{rs::minmax(nums_)};

    // Extract numbers in the [min, max] range not present in the input
    return 
        vs::iota(minNum, maxNum + 1) |
        vs::filter([&] (auto const num_) { return !numsMask.test(num_); }) |
        rs::to<numsT>()
    ; 
}
