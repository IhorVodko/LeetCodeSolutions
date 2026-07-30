// problem : https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-i/description
// submission : https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-i/submissions/2087822923
// solution post : https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-i/solutions/8431152/
//    simplanation-simple-explanation-by-cyber-wyww

// Approach : Approach : Constant Time Arithmetic Progression
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// Time :  O(n)
// Space : O(1)

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

// Available letter keys on standard telephone keypad
auto constexpr kTotKeys{8};

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
    static auto minimumPushes(std::string_view const word_) -> int;
};

auto Solution::minimumPushes(std::string_view const word_) -> int {
    // Extract quotient and remainder for optimal key distribution
    auto const [qout, rem]{std::div(static_cast<int>(word_.size()), kTotKeys)};

    // Sum pushes via arithmetic progression for full rounds, plus leftovers
    return qout * (2 * kTotKeys + (qout - 1) * kTotKeys) / 2 + rem * (qout + 1);
}
