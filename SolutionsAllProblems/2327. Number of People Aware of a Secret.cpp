// problem : https://leetcode.com/problems/number-of-people-aware-of-a-secret/description/
// submission : https://leetcode.com/problems/number-of-people-aware-of-a-secret/submissions/1765124203
// solution post : https://leetcode.com/problems/number-of-people-aware-of-a-secret/solutions/7172961/
//    c-modern-readable-code-optimal-time-comp-1ipn

// #include <dequeue>
// #include <ranges>
// #include <vector>

class Solution {
public:
// let 'n' be a given days duration
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    int peopleAwareOfSecret(
        int const durationDays_,
        int const delayDays_,
        int const forgetDays_
    ) const;
private:
    static int constexpr mkModVal{1'000'000'007};
};

int Solution::peopleAwareOfSecret(
    int const durationDays_,
    int const delayDays_,
    int const forgetDays_
) const {
    namespace views = std::views;
    auto keepSecret{std::deque<std::pair<int, int>>{}};
    auto shareSecret{std::deque<std::pair<int, int>>{}};
    keepSecret.emplace_back(1, 1);
    auto keepSecretPeopleCnt{1};
    auto shareSecretPeopleCnt{0};
    for(auto const dayCount: views::iota(2, durationDays_ + 1)) {
        auto const daysToKeepLeft{dayCount - delayDays_};
        if( !keepSecret.empty() &&
            keepSecret.front().first == daysToKeepLeft
        ) {
            auto const currKeepSecretPeopleCnt{keepSecret.at(0).second};
            keepSecretPeopleCnt =
                (keepSecretPeopleCnt - currKeepSecretPeopleCnt + mkModVal)
                % mkModVal;
            shareSecretPeopleCnt =
                (shareSecretPeopleCnt + currKeepSecretPeopleCnt) % mkModVal;
            shareSecret.emplace_back(keepSecret.front());
            keepSecret.pop_front();
        }
        auto const daysToRememberLeft{dayCount - forgetDays_};
        if( !shareSecret.empty() &&
            shareSecret.at(0).first == daysToRememberLeft
        ) {
            auto const currShareCnt{shareSecret.at(0).second};
            shareSecretPeopleCnt =
                (shareSecretPeopleCnt - currShareCnt + mkModVal) % mkModVal;
            shareSecret.pop_front();
        }
        if(!shareSecret.empty()) {
            keepSecretPeopleCnt =
                (keepSecretPeopleCnt + shareSecretPeopleCnt) % mkModVal;
            keepSecret.emplace_back(dayCount, shareSecretPeopleCnt);
        }
    }
    auto const knowPeopleCnt{
        (keepSecretPeopleCnt + shareSecretPeopleCnt) % mkModVal};
    return knowPeopleCnt;
}
