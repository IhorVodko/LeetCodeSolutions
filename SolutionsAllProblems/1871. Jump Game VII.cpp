// problem : https://leetcode.com/problems/jump-game-vii/description
// submission : https://leetcode.com/problems/jump-game-vii/submissions/2012777413
// solution post : https://leetcode.com/problems/jump-game-vii/solutions/8293130/c-modern-readable-code-beats-100-runtime-69gz

// Approach : Dynamic Programming with Sliding Window
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the string length
// complexity :  O(n)
// complexity : O(n)

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto canReach(
        std::string_view const str_,
        int const jmpLowLim_,
        int const jmpUpLim_
    ) -> bool;

private:
    static auto constexpr kZero{'0'};
    static auto constexpr kOne{'1'};
    static auto constexpr kIsNotReachable{'0'};
    static auto constexpr kIsReachable{'1'};
};

auto Solution::canReach(
    std::string_view const str_,
    int const jmpLowLim_,
    int const jmpUpLim_
) -> bool {
    namespace vs = std::views;

    // Early exit if the target destination is fundamentally invalid.
    if(str_.back() == kOne) {
        return false;
    }

    auto const len{std::ssize(str_)};
    // Reachability state per index based on preceding jumps.
    auto dp{std::vector<char>(len, kIsNotReachable)};
    dp[0] = kIsReachable;
    // Count of valid, active launch points in the current window.
    auto jmps{0};

    for(auto const currIdx: vs::iota(1, len)) {
        // Incorporates a newly available launch point from minJump distance.
        if(jmpLowLim_ <= currIdx && dp[currIdx - jmpLowLim_] == kIsReachable) {
            ++jmps;
        }
        // Expires a launch point that has fallen out of the maxJump range.
        if(jmpUpLim_ < currIdx && dp[currIdx - jmpUpLim_ - 1] == kIsReachable) {
            --jmps;
        }
        if(0 < jmps && str_[currIdx] == kZero) {
            dp[currIdx] = kIsReachable;
        }
    }

    return dp.back() == kIsReachable;
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
