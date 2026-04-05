// problem : https://leetcode.com/problems/robot-return-to-origin/description
// submission : https://leetcode.com/problems/robot-return-to-origin/submissions/1969662086
// solution post : https://leetcode.com/problems/robot-return-to-origin/solutions/7786565/c-modern-readable-code-beats-100-runtime-9jpi

// import std;

// let 'n' be the number of moves
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    [[nodiscard]]
    auto judgeCircle(std::string_view const moves_) -> bool;
};

auto Solution::judgeCircle(std::string_view const moves_) -> bool {
    namespace vs = std::views;

    // Track the net displacement along the horizontal and vertical axes
    auto x{0};
    auto y{0};

    // Adjust coordinates based on the direction of each step
    for(auto const move: moves_) {
        switch(move) {
            case 'L': { --x; break; }
            case 'R': { ++x; break; }
            case 'D': { --y; break; }
            case 'U': { ++y; break; }
        }
    }

    // The robot is back at the origin if all opposite moves cancel out perfectly
    return x == 0 && y == 0;
}

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
