// problem : https://leetcode.com/problems/combinations/description
// submission : https://leetcode.com/problems/combinations/submissions/1734947702
// solution post : https://leetcode.com/problems/combinations/solutions/7080198/
//    c-modern-readable-code-optimal-time-comp-zzth

// #include <ranges>
// #include <vector>

#include <ranges>

namespace Util {
    inline auto constexpr kFirstNum{1};
}

class Solution {
public:
    using mxT = std::vector<std::vector<int>>;
// let 'n' be a maximum number given
// 's' - size of the combination given
// time complexity O(n! / (s - 1)! * (n - s)!)
// space complexity O(s)
// runtime 31 ms, beats 98.96 %
    mxT combine(
        int const maxNum_,
        int const numsSz_
    );
private:
    void Backtrack(
        std::vector<int> & comb_,
        mxT & combs,
        int const firstNum_
    ) const;
    int mMaxNum{};
    int mCombSz{};
};

Solution::mxT Solution::combine(
    int const maxNum_,
    int const combSz_
) {
    using namespace Util;
    mMaxNum = maxNum_;
    mCombSz = combSz_;
    mxT combs;
    auto comb{std::vector<int>{}};
    comb.reserve(combSz_);
    Backtrack(comb, combs, kFirstNum);
    return combs;
}

void Solution::Backtrack(
    std::vector<int> & comb_,
    mxT & combs_,
    int const firstNum_
) const {
    namespace views = std::views;
    auto const combSz{std::ssize(comb_)};
    if(combSz == mCombSz) {
        combs_.emplace_back(comb_);
        return;    
    }
    auto const numsNeededSz{mCombSz - combSz};
    auto const numsRemainedSz{mMaxNum - firstNum_ + 1};
    auto const numsAvailableSz{numsRemainedSz - numsNeededSz};
    auto const lastNum{firstNum_ + numsAvailableSz + 1};
    for(auto const num: views::iota(firstNum_, lastNum)) {
        comb_.emplace_back(num);
        Backtrack(comb_, combs_, num + 1);
        comb_.pop_back();
    }
}
