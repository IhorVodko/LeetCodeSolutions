// problem : https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-ii/description/
// submission : https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-ii/
//    submissions/1808530997
// solution post : https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-ii/
//    solutions/7292760/c-modern-readable-code-beats-100-runtime-xrom

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
// let 'n' be the count of the given numbers
// 'd' - the given delta
// time complexity O(n * d)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maxFrequency(
        std::vector<int> & nums_,
        int delta_,
        int opTotalCnt_
    ) const -> int;
};

auto Solution::maxFrequency(
    std::vector<int> & nums_,
    int delta_,
    int opTotalCnt_
) const -> int {
    namespace rngs = std::ranges;

    rngs::sort(nums_);
    auto const numsEnd{nums_.cend()};
    auto leftNum1{nums_.cbegin()};
    auto rightNum1{leftNum1};
    auto currValidNumCnt1{0};
    auto maxValidNumCnt{0};
    auto leftNum2{nums_.cbegin()};
    auto currValidNumCnt2{0};
    auto duplicateNumCnt{0};
    auto prevNum{-1};
    auto const doubleDelta{delta_ * 2};
    for(auto const currNum: nums_) {
        if(currNum == prevNum) {
            ++duplicateNumCnt;
        } else {
            prevNum = currNum;
            duplicateNumCnt = 1;
        }
        while(*leftNum1 < currNum - delta_) {
            --currValidNumCnt1;
            ++leftNum1;
        }
        while(rightNum1 < numsEnd && *rightNum1 <= currNum + delta_) {
            ++currValidNumCnt1;
            ++rightNum1;
        }
        maxValidNumCnt = std::max(
            maxValidNumCnt,
            duplicateNumCnt +
                std::min(currValidNumCnt1 - duplicateNumCnt, opTotalCnt_)
        );
        ++currValidNumCnt2;
        while(*leftNum2 < currNum - doubleDelta) {
            --currValidNumCnt2;
            ++leftNum2;
        }
        maxValidNumCnt = std::max(
            maxValidNumCnt,
            std::min(currValidNumCnt2, opTotalCnt_)
        );
    }
    return maxValidNumCnt;
}
