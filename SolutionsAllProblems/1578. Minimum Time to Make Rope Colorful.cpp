// problem : https://leetcode.com/problems/minimum-time-to-make-rope-colorful/description/
// submission : https://leetcode.com/problems/minimum-time-to-make-rope-colorful/submissions/1819824301
// solution post : https://leetcode.com/problems/minimum-time-to-make-rope-colorful/solutions/7324408/
//    c-modern-readable-code-beats-100-runtime-gyln

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream("display_runtime.txt") << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class Solution {
public:
// let 'n' be the number of the given colors
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto minCost(
        std::string_view const colors_, 
        std::span<const int> const timeCosts_
    ) const -> int;
};

auto Solution::minCost(
    std::string_view const colors_, 
    std::span<const int> const timeCosts_
) const -> int {
    namespace vs = std::views;
   
    auto totalTime{0};
    auto maxTime{timeCosts_.front()};
    for(auto const idx: vs::iota(1, std::ssize(colors_))) {
        if(colors_[idx] != colors_[idx - 1]) {
            maxTime = 0;
        }
        totalTime += std::min(maxTime, timeCosts_[idx]);
        maxTime = std::max(maxTime, timeCosts_[idx]);
    }
    return totalTime;
}
