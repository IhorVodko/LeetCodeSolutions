// problem : https://leetcode.com/problems/jump-game-ix/description
// submission : https://leetcode.com/problems/jump-game-ix/submissions/1997442370
// solution post : https://leetcode.com/problems/jump-game-ix/solutions/8161770/c-modern-readable-code-dynamic-programmi-xyv3

// Approach : Prefix Maximum and Suffix Minimum Precomputation with Backwards Dynamic Programming
// Runtime : 11 ms, beats 69.15 %

// Complexity
// let 'n' be the count of given numbers
// complexity :  O(n)
// complexity : O(n)

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
    using numsT = std::vector<int>;

    [[nodiscard]]
    auto maxValue(numsT const & nums_) const -> numsT;
};

auto Solution::maxValue(numsT const & nums_) const -> numsT {
    namespace vs = std::views;

    auto const numsSz{std::ssize(nums_)};

    // 1. Compute forward running maximum numbers
    auto prefMaxNums{numsT{}};
    prefMaxNums.reserve(numsSz);
    prefMaxNums.emplace_back(nums_.front());

    // 2. Compute backward running minimum numbers
    auto sufMinNums{numsT(numsSz)};
    sufMinNums.back() = nums_.back();

    for(auto const j: vs::iota(1, numsSz)) {
        prefMaxNums.emplace_back(std::max(prefMaxNums.back(), nums_[j]));
        auto const suffIdx{numsSz - j - 1};
        sufMinNums[suffIdx] = std::min(sufMinNums[suffIdx + 1], nums_[suffIdx]);
    }

    // 3. For each given nubmer compute maximum number that can be reached following the
    //    game rules. Use backwards dynamic programming
    auto maxNums{numsT(numsSz)};
    maxNums.back() = prefMaxNums.back();

    for(auto const j: vs::iota(0, numsSz - 1) | vs::reverse) {
        auto const prefMaxNum{prefMaxNums[j]};
        maxNums[j] = prefMaxNum > sufMinNums[j + 1] ? 
            std::max(prefMaxNum, maxNums[j + 1]) : prefMaxNum;
    }

    return maxNums;
}
