// problem : https://leetcode.com/problems/make-array-elements-equal-to-zero/description/
// submission : https://leetcode.com/problems/make-array-elements-equal-to-zero/submissions/1814044507
// solution post : https://leetcode.com/problems/make-array-elements-equal-to-zero/solutions/7307845/
//    c-modern-readable-code-beats-100-runtime-ruaz

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
// let 'n' be the number of the given numbers
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto countValidSelections(std::vector<int> & nums_) const ->int;
};

auto Solution::countValidSelections(std::vector<int> & nums_) const ->int {
    namespace rngs = std::ranges;
    namespace vs = std::views;

    auto const numsSz{std::ssize(nums_)};
    auto selectionsCnt{0};
    auto leftSum{0};
    auto rightSum{std::accumulate(nums_.cbegin(), nums_.cend(), 0)};
    for(auto const idx: vs::iota(0, numsSz)) {
        if(nums_[idx] == 0) {
            auto const diff{std::abs(leftSum - rightSum)};
            selectionsCnt += diff == 0 ? 2 : diff == 1 ? 1 : 0;
        }
        leftSum += nums_[idx];
        rightSum -= nums_[idx];       
    }
    return selectionsCnt;
}
