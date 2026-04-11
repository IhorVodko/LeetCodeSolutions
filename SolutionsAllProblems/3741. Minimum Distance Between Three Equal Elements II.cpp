// problem : https://leetcode.com/problems/minimum-distance-between-three-equal-elements-ii/description/
// submission : https://leetcode.com/problems/minimum-distance-between-three-equal-elements-ii/submissions/1975718308
// solution post : https://leetcode.com/problems/minimum-distance-between-three-equal-elements-ii/
//    solutions/7875105/c-modern-readable-code-by-cyberartist-o7re

// Approach : Hash Map Next-Occurrence Chaining
// Runtime : 166 ms, beats 97.75 %

// Complexity
// let 'n' be the length of the array of numbers
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
    using intLim = std::numeric_limits<int>;

    [[nodiscard]]
    auto minimumDistance(std::vector<int> const & nums_) const -> int;

private:
    static auto constexpr kNoAnswer{-1};
    static auto constexpr kIsNotPresent{-1};
    static auto constexpr kMinIdxCnt{3};
};

auto Solution::minimumDistance(std::vector<int> const & nums_) const -> int {
    namespace vs = std::views;

    auto const numsSz{static_cast<int>(nums_.size())};

    if(numsSz < kMinIdxCnt) {
        return kNoAnswer;
    }

    auto nextIdxs{std::vector<int>(numsSz, kIsNotPresent)};
    auto numToIdx{std::unordered_map<int, int>{}};

    numToIdx.reserve(numsSz);

    auto maxDist{intLim::max()};

    // Traverse backwards to construct a chain of next-occurrence indices for O(1)
    // traversal
    for(auto const j: vs::iota(0, numsSz) | vs::reverse) {
        auto const num{nums_[j]};

        if(auto const numToIdxIt{numToIdx.find(num)}; numToIdxIt != numToIdx.end()) {
            nextIdxs[j] = numToIdxIt->second;
        }

        numToIdx[num] = j;
    }

    // Evaluate valid triplets to find the minimum distance span between the first and
    // third elements
    for(auto const leftIdx: vs::iota(0, numsSz)) {
        auto const middleIdx{nextIdxs[leftIdx]};

        if(middleIdx == kIsNotPresent) {
            continue;
        }

        auto const rightIdx{nextIdxs[middleIdx]};

        if(rightIdx == kIsNotPresent) {
            continue;
        }

        auto const currDist{rightIdx - leftIdx};
        maxDist = std::min(maxDist, currDist);
    }
    
    return (maxDist == intLim::max()) ? kNoAnswer : (maxDist * 2);
}
