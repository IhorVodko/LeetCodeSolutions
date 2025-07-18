// problem : https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-ii/description
// submission : https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-ii/submissions/1702368218
// solution post : https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-ii/solutions/6974117/
//    c-modern-readable-code-optimal-time-comp-wpm5

// #include <algorithm>
// #include <ranges>
// #include <vector>

class Solution {
public:
// let 'n' be a count of the given numbers
// 'm' - modulo value
// time complexity O(m^2 + n * m)
// space complexity O(m^2)
// runtime 174 ms, beats 20.30 %
    [[nodiscard]]
    int maximumLength(
        std::vector<int> const & lastNumReminders_,
        int const modVal_
    ) const;
};

int Solution::maximumLength(
    std::vector<int> const & lastNumReminders_,
    int const modVal_
) const {
    namespace views = std::views;
    using MxT = std::vector<std::vector<int>>;
    auto prevAndLastNumReminders{
        MxT( modVal_, std::vector<int>( modVal_, 0))};
    auto subseqSzMax{ 0};
    for(auto num: lastNumReminders_) {
        auto const lastNumReminder{ num % modVal_};
        for(auto const prevNumReminder: views::iota( 0, modVal_)) {
            auto & subseqSzCurr{ prevAndLastNumReminders
                .at( prevNumReminder)
                .at( lastNumReminder)};
            auto & subseqSzPrev{ prevAndLastNumReminders
                .at( lastNumReminder)
                .at( prevNumReminder)};
            subseqSzCurr = subseqSzPrev + 1;
            subseqSzMax = std::max( subseqSzMax, subseqSzCurr);
        }
    }
    return subseqSzMax;
}
