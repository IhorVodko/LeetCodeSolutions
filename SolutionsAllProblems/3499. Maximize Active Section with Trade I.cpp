// problem : https://leetcode.com/problems/maximize-active-section-with-trade-i/description
// submission : https://leetcode.com/problems/maximize-active-section-with-trade-i/submissions/2076237117
// solution post : https://leetcode.com/problems/maximize-active-section-with-trade-i/solutions/8411877/
//  modern-readable-code-optimal-time-comple-shx1

// Approach : Greedy Adjacent Inactive Block Maximization
// Runtime : 32 ms, beats 95.50 %

// Complexity analysis
// let 'n' be the number of elements in the string
// Time :  O(n)
// Space : O(1)

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

auto constexpr kZero{'0'};

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
    static auto maxActiveSectionsAfterTrade(std::string_view const str_) -> int;
};

auto Solution::maxActiveSectionsAfterTrade(std::string_view const str_) -> int {

    auto totOnes{0};
    auto prevZeroBlckLen{-1};
    auto maxGain{0};
    auto cntZeroBlcks{0};

    // Segment string into continuous identical blocks
    for(auto const chunk: str_ | vs::chunk_by(std::equal_to{})) {
        auto const chunkLen{static_cast<int>(rs::distance(chunk))};

        if(chunk.front() == kZero) {
            ++cntZeroBlcks;

            if(prevZeroBlckLen != -1) {
                // Track best yield from two consecutive inactive blocks
                auto const currGain{prevZeroBlckLen + chunkLen};
                maxGain = std::max(maxGain, currGain);
            }

            prevZeroBlckLen = chunkLen;
        } else {
            totOnes += chunkLen;
        }
    } 

    // A valid trade requires at least two inactive blocks
    return cntZeroBlcks < 2 ? totOnes : totOnes + maxGain;
}
