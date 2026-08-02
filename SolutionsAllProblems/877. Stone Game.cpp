// problem : https://leetcode.com/problems/stone-game/description
// submission : https://leetcode.com/problems/stone-game/submissions/2091515373
// solution post : https://leetcode.com/problems/stone-game/solutions/8437048/simplanation-simple-explanation-by-cyber-efe3

// Approach : Game Theory & Mathematical Parity
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// Time :  O(1)
// Space : O(1)

// import std;

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

class Solution final {
public:
    [[nodiscard]]
    static auto stoneGame(std::vector<int> const & piles_) -> bool;
};

auto Solution::stoneGame(std::vector<int> const & piles_) -> bool {
    // Alice controls the game parity and can always secure the winning sum.
    return true;
}
