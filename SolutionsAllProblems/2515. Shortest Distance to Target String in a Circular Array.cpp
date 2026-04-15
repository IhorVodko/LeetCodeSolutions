// problem : https://leetcode.com/problems/shortest-distance-to-target-string-in-a-circular-array/description
// submission : https://leetcode.com/problems/shortest-distance-to-target-string-in-a-circular-array/submissions/1979189402
// solution post : https://leetcode.com/problems/shortest-distance-to-target-string-in-a-circular-array/solutions/7924730/
//    c-modern-readable-code-beats-100-runtime-4xid

// Approach : Linear Scan with Bidirectional Distance Evaluation
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the number of words
// 'm' - target word legth
// complexity :  O(n * m)
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
    auto closestTarget(
        std::vector<std::string> const & words_,
        std::string_view const target_,
        int const startIdx
    ) const -> auto;

private:
    static auto constexpr kMax{std::numeric_limits<int>::max()};
};

auto Solution::closestTarget(
    std::vector<std::string> const & words_,
    std::string_view const target_,
    int const startIdx
) const -> auto {
    namespace vs = std::views;

    auto minDist{kMax};
    auto const wordsLen{static_cast<int>(words_.size())};

    for(auto const j: vs::iota(0, wordsLen)) {
        if(words_[j] == target_) {
            // Calculate the absolute distance without considering circularity
            auto const nonCircDist{std::abs(j - startIdx)};
            // Calculate the circular distance by going the opposite direction
            auto const circDist{wordsLen - nonCircDist};;

            minDist = std::min({minDist, nonCircDist, circDist});
        }
    }
    
    // Return -1 if target was never found, otherwise return the minimum distance
    return minDist == kMax ? -1 : minDist;
}
