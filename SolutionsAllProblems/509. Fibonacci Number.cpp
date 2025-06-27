// problem : https://leetcode.com/problems/fibonacci-number/description
// submission : https://leetcode.com/problems/fibonacci-number/submissions/1678387066
// solution post : https://leetcode.com/problems/fibonacci-number/solutions/6892509/
//    c-modern-readable-code-beats-100-runtime-6beu

// #include <array>

namespace Util {
    inline auto constexpr kNthMax{31};
}

class Solution {
public:
// let 'n' be a positional count of the required number to find
// time complexity O(n)
// space complexity O(max possible n)
// runtime 0 ms, beats 100.00 %
    int fib(int const nth_);
private:
    int DoFib(int const nth_);
    std::array<int, Util::kNthMax> mMemo{};
};

int Solution::fib(int const nth_) {
       mMemo.fill(-1); 
       DoFib(nth_);
       return mMemo.at(nth_);
}

int Solution::DoFib(int const nth_) {
    if(mMemo.at(nth_) != -1) {
        return mMemo.at(nth_);
    }
    if(nth_ == 0) {
        mMemo.at(0) = 0;
        return 0;
    } else if(nth_ == 1) {
        mMemo.at(1) = 1;
        return 1;
    }
    auto nthNum{DoFib(nth_ - 1) + DoFib(nth_ - 2)}; 
    mMemo.at(nth_) = nthNum;
    return nthNum;
}
