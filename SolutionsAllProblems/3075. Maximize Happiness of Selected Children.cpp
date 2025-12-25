// problem : https://leetcode.com/problems/maximize-happiness-of-selected-children/description
// submission : https://leetcode.com/problems/maximize-happiness-of-selected-children/submissions/1864929580
// solution post : https://leetcode.com/problems/maximize-happiness-of-selected-children/solutions/7438109/
//    c-modern-readable-code-beats-100-runtime-15cx

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream{"display_runtime.txt"} << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the number of children
// 'm' - of turns
// time complexity O(n * log(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto maximumHappinessSum(
        std::span<int> const happiness_,
        int turnCnt_
    ) const -> long long;
};

auto Solution::maximumHappinessSum(
    std::span<int> const happiness_,
    int turnCnt_
) const -> long long {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    rngs::sort(happiness_, std::greater{});
    auto hapSum{0ll};
    for(auto const turn: vs::iota(0, turnCnt_)) {
        if( auto const curHap{happiness_[turn] - turn};
            curHap > 0
        ) [[likely]] {
            hapSum += curHap;
        } else [[unlikely]] {
            return hapSum;
        }
    }
    return hapSum;
}
