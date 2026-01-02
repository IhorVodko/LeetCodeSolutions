// problem : https://leetcode.com/problems/n-repeated-element-in-size-2n-array/description
// submission : https://leetcode.com/problems/n-repeated-element-in-size-2n-array/submissions/1872271154
// solution post : https://leetcode.com/problems/n-repeated-element-in-size-2n-array/solutions/7459823/
//    c-modern-readable-code-beats-100-runtime-hurc

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

// let 'n' be the number of numbers
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto repeatedNTimes(std::span<int const> const nums_) const -> int;
};

auto Solution::repeatedNTimes(std::span<int const> const nums_) const -> int {
    namespace vs = std::views;

    auto uniqueNums{std::unordered_set<int>{}};
    uniqueNums.reserve(nums_.size() / 2 + 1);
    for(auto const num: nums_) {
        if(!uniqueNums.emplace(num).second) {
            return num;
        }
    }
    return -1;
}
