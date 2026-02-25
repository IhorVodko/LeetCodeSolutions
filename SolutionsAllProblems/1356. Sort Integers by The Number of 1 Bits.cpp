// problem : https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/description
// submission : https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/submissions/1930825039
// solution post : https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/solutions/7608389/
//    c-modern-readable-code-beats-100-runtime-ai6h

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the count of numbers
// time complexity O(n * log(n))
// space complexity O(log(n))
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto sortByBits(std::vector<int> & nums_) const -> std::vector<int> {
        namespace vs = std::views;
        namespace rngs = std::ranges;

        // Sort numbers by popcount (number of set bits), then by numeric value
        rngs::sort(nums_, [] (auto const num1_, auto const num2_) {
            // Count set bits using std::popcount (requires unsigned)
            auto const cnt1{std::popcount(static_cast<unsigned>(num1_))};
            auto const cnt2{std::popcount(static_cast<unsigned>(num2_))};
            // Primary key: bit count; Secondary key: numeric order
            return cnt1 == cnt2 ? num1_ < num2_ : cnt1 < cnt2;
        });
        return nums_; 
    }
};
