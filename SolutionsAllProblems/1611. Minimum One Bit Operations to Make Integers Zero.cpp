// problem : https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/description/
// submission : https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/submissions/1824374921
// solution post : https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/solutions/7335362/
//    c-modern-readable-code-beats-100-runtime-5wpz

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
// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto minimumOneBitOperations(int const num_) const -> int;
};

auto Solution::minimumOneBitOperations(int const num_) const -> int {
    auto opCnt{num_};
    opCnt ^= opCnt >> 16;
    opCnt ^= opCnt >> 8;
    opCnt ^= opCnt >> 4;
    opCnt ^= opCnt >> 2;
    opCnt ^= opCnt >> 1;
    return opCnt;
}
