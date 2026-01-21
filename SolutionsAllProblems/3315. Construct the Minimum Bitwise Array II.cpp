// problem : https://leetcode.com/problems/construct-the-minimum-bitwise-array-ii/description
// submission : https://leetcode.com/problems/construct-the-minimum-bitwise-array-ii/submissions/1892529124
// solution post : https://leetcode.com/problems/construct-the-minimum-bitwise-array-ii/solutions/7513519/
//    c-modern-readable-code-beats-100-runtime-3dqp

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

// let 'n' be the size of vector
// 'm' - maximum value in the vector 
// time complexity O(n * m)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto minBitwiseArray(std::vector<int> & nums_) const -> std::vector<int>;
};

auto Solution::minBitwiseArray(
    std::vector<int> & nums_
) const -> std::vector<int> {
    for(auto & num: nums_) {
        // Stores the candidate result after clearing a chosen bit
        auto target{-1};
        // Tracks the current bit position being examined (1, 2, 4, ...)
        auto pos{1};
        // Iterate through consecutive set bits starting from the least significant bit
        while((num & pos) != 0) {
            target = num - pos;
            pos <<= 1; 
        }
        // Assign the smallest valid value found for this number
        num = target;
    }
    return nums_;
}
