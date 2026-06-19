// problem : https://leetcode.com/problems/find-the-highest-altitude/description
// submission : https://leetcode.com/problems/find-the-highest-altitude/submissions/2039107225
// solution post : https://leetcode.com/problems/find-the-highest-altitude/solutions/8345832/c-modern-readable-code-beats-100-runtime-6y5l

// Approach : Prefix Sum / Single Pass
// Runtime : 0 ms, beats 100.00 %


// Complexity
// let 'n' be the number of gains
// Time :  O(n)
// Space : O(1)

// import std;

#define NDEBUG

#include <cassert>

#ifdef NDEBUG
    #define Cond(...)       ((void)0)
    #define PreCond(...)    Cond(__VA_ARGS__)
    #define PostCond(...)   Cond(__VA_ARGS__)
#else
    #define Cond(...)       assert(                                 \
        ([] (std::convertible_to<bool> auto && ... preds_) {        \
            return (... && preds_);                                 \
        }) (__VA_ARGS__)                                            \
    )
    #define PreCond(...)    Cond(__VA_ARGS__)
    #define PostCond(...)   Cond(__VA_ARGS__)
#endif

class Solution final {
public:
    [[nodiscard]]
    static auto largestAltitude(std::vector<int> const & gains_) -> int;
};

auto Solution::largestAltitude(std::vector<int> const & gains_) -> int {
    namespace rs = std::ranges;

    PreCond(
        rs::all_of(gains_, [] (auto const gain_) {
            return -100 <= gain_ && gain_ <= 100;
        }),
        1 <= gains_.size(), gains_.size() <= 100
    );

    // State transition computing next max and current altitude
    auto const CompMaxAlt{[&] (
        auto const & maxAndCurrAlts_,
        auto const gain_
    ) -> std::pair<int, int> {
        auto const [maxAlt, currAlt]{maxAndCurrAlts_};
        auto const newAlt{currAlt + gain_};
        return {std::max(maxAlt, newAlt), newAlt};
    }};

    // Execute fold with initial max and current altitudes at 0
    auto const maxAlt{rs::fold_left(gains_, std::pair{0, 0}, CompMaxAlt).first};

    PostCond(-100 * 100 <= maxAlt, maxAlt <= 100 * 100);

    return maxAlt;
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
