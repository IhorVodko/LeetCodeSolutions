// problem : https://leetcode.com/problems/closest-equal-element-queries/description
// submission : https://leetcode.com/problems/closest-equal-element-queries/submissions/1980399367
// solution post : https://leetcode.com/problems/closest-equal-element-queries/solutions/7947686/c-modern-readable-code-beats-100-runtime-4gf9

// Approach : Simulated Circular Array with Hash Map
// Runtime : 87 ms, beats 100.00 %

// Complexity
// let 'n' be the length of the array of numbers
// 'm' - number of queries
// complexity :  O(n + m)
// complexity : O(n)

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
    auto solveQueries(
        std::vector<int> const & nums_, 
        std::vector<int> const & queries_
    ) const -> std::vector<int>;
};

auto Solution::solveQueries(
    std::vector<int> const & nums_, 
    std::vector<int> const & queries_
) const -> std::vector<int> {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const numsSz{static_cast<int>(nums_.size())};
    // Initialize distances with an upper bound acting as infinity
    auto minDists{std::vector<int>(numsSz, numsSz)};

    // Map each unique number to its last seen virtual index
    auto numToLastVirtIdx{std::unordered_map<int, int>{}};
    numToLastVirtIdx.reserve(numsSz);

    // Iterate twice over the array to simulate a circular lookup for closest equal
    // elements. Calculates direct (non-circular) distance during the first array pass
    // (currVirtIdx < numsSz). Calculates circular distance during the second array pass
    // (currVirtIdx >= numsSz)
    for(auto const currVirtIdx: vs::iota(0, numsSz * 2)) {
        auto const currRealIdx{currVirtIdx % numsSz};
        auto const num{nums_[currRealIdx]};

        if(auto const numAndLastVirtIdxIt{numToLastVirtIdx.find(num)};
            numAndLastVirtIdxIt != numToLastVirtIdx.end()
        ) {
            auto const prevRealIdx{numAndLastVirtIdxIt->second % numsSz};
            auto const currDist{currVirtIdx - prevRealIdx};
            auto & currMinDist{minDists[currRealIdx]};

            currMinDist = std::min(currMinDist, currDist);

            auto & prevMinDist{minDists[prevRealIdx]};
            
            // Bidirectional update ensures both left and right closest matches are
            // recorded
            prevMinDist = std::min(prevMinDist, currDist);
        }

        numToLastVirtIdx[num] = currVirtIdx;
    }

    // Process all queries in O(1) time each using the precalculated distances
    auto const minDistsOut{
        queries_ |
        vs::transform(
            [
                &minDists_ = std::as_const(minDists),
                numsSz_ = std::as_const(numsSz)
            ] (auto const qr_) {
                auto const & minDist{minDists_[qr_]};
                return minDist == numsSz_ ? -1 : minDist;
        }) |
        rngs::to<std::vector>()
    };

    return minDistsOut;
}
