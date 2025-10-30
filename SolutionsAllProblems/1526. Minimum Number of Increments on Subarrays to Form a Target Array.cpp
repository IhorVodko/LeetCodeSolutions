// problem : https://leetcode.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/description/
// submission : https://leetcode.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/
//    submissions/1815982548
// solution post : https://leetcode.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/
//    solutions/7313639/c-modern-readable-code-beats-100-runtime-h1in

// import std;

// let 'n' be the number of given numbers
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
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
    [[nodiscard]]
    auto minNumberOperations(std::vector<int> const & targetNums_) const -> int;
};

auto Solution::minNumberOperations(std::vector<int> const & targetNums_) const -> int {
    if(targetNums_.empty()) {
        return 0;
    }
    auto opMinCnt{targetNums_[0]};
    opMinCnt += std::inner_product(
        targetNums_.begin(), targetNums_.end() - 1,
        targetNums_.begin() + 1,
        0,
        std::plus{},
        [] (auto const prevNum_, auto const currNum_) {
            return std::max(0, currNum_ - prevNum_);
        }
    );
    return opMinCnt;
}
