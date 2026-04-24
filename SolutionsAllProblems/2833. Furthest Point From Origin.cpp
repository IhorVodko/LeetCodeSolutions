// problem : https://leetcode.com/problems/furthest-point-from-origin/description
// submission : https://leetcode.com/problems/furthest-point-from-origin/submissions/1987175131
// solution post : https://leetcode.com/problems/furthest-point-from-origin/solutions/8095589/
//    c-modern-readable-code-beats-100-runtime-laef

// Approach : Greedy / Linear Scan
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the number of moves
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
    auto furthestDistanceFromOrigin(std::string_view const moves_) const noexcept -> int;

private:
    static auto constexpr kL{'L'};
    static auto constexpr kR{'R'};
    static auto constexpr kWildcard{'_'};
};

auto Solution::furthestDistanceFromOrigin(
    std::string_view const moves_
) const noexcept -> int {
    // Tracks net distance from 'L' and 'R', and counts '_' wildcards
    auto netDist{0};
    auto wildcardCnt{0};

    for(auto const move: moves_) {
        if(move == kWildcard) {
            ++wildcardCnt;
        } else {
            netDist += move == kL ? -1 : 1;
        }
    }

    // Add all wildcards to the absolute net distance for max distance
    auto const maxDist{std::abs(netDist) + wildcardCnt};

    return maxDist;
}
