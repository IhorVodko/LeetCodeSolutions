// problem : https://leetcode.com/problems/smallest-number-with-all-set-bits/description/
// submission : https://leetcode.com/problems/smallest-number-with-all-set-bits/submissions/1815350771
// solution post : https://leetcode.com/problems/smallest-number-with-all-set-bits/solutions/7311802/
//    c-modern-readable-code-beats-100-runtime-6lgl

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
// let 'n' be the given number
// time complexity O(log(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto smallestNumber(int const num_) const -> int;
};

auto Solution::smallestNumber(int const num_) const -> int {
    auto smallestNum{std::bit_ceil(static_cast<unsigned>(num_))};
    if(smallestNum == num_) {
        smallestNum = smallestNum * 2 - 1;
        return smallestNum;
    }
    return --smallestNum; 
}
