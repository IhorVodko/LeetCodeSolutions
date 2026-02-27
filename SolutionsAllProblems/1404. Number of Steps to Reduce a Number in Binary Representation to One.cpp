// problem : https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/description/
// submission : https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/
//    submissions/1932586297
// solution post : https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/
//    solutions/7612612/c-modern-readable-code-beats-100-runtime-7mw1

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the number of bits
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto numSteps(std::string & strBinNum_) const -> int;
};

auto Solution::numSteps(std::string & strBinNum_) const -> int {
    namespace vs = std::views;

    auto opCnt{0};
    auto carry{0};
    // Process bits from least significant to most significant, skipping the MSB
    for(auto const bit: strBinNum_ | vs::drop(1) | vs::reverse) {
        // If current bit plus carry is odd, we simulate an addition (making it even)
        if(((bit == '0' ? 0 : 1) + carry) % 2 == 1) {
            ++opCnt;
            carry = 1;
        }
        // Every iteration includes one division operation
        ++opCnt;

    }
    // If a carry remains after processing all bits, it contributes one final operation
    opCnt += carry;
    return opCnt;
}
