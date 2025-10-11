// problem : https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/description/
// submission : https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/submissions/1798145062
// solution post : https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/solutions/7266434/
//    c-modern-readable-code-beats-100-runtime-ndxi

// import std;

class Solution {
public:
// let 'j' be the number of the given job difficulties
// 'd' - the number of the given days
// time complexity O(j * d)
// space complexity O(j)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto minDifficulty(
        std::vector<int> const & jobDifficulties_,
        int const daysCnt_
    ) const -> int;

private:
    inline static int constexpr kMaxjobDifficulties_{1'000};
    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
};

auto Solution::minDifficulty(
    std::vector<int> const & jobDifficulties_,
    int const daysCnt_
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    using limitsIntT = std::numeric_limits<int>;

    auto const jobsSz{std::ssize(jobDifficulties_)};
    if(jobsSz < daysCnt_) {
        return -1;
    }
    auto minDiffPrevDay{std::vector<int>(jobsSz, kMaxjobDifficulties_)};
    auto minDiffCurrDay{std::vector<int>(jobsSz, kMaxjobDifficulties_)};
    for(auto const day: vs::iota(0, daysCnt_)) {
        auto stckJobIdxs{std::stack<int>{}};
        for(auto const jobIdx: vs::iota(day, jobsSz)) {
            minDiffCurrDay.at(jobIdx) = jobIdx == 0 ?
                jobDifficulties_.at(0) :
                minDiffPrevDay.at(jobIdx - 1) + jobDifficulties_.at(jobIdx)
            ;
            while(
                !stckJobIdxs.empty() &&
                jobDifficulties_.at(stckJobIdxs.top()) <=
                    jobDifficulties_.at(jobIdx)
            ) {
                auto const jobIdxTop{stckJobIdxs.top()};
                stckJobIdxs.pop();
                auto const diffIncr{
                    jobDifficulties_.at(jobIdx) -
                    jobDifficulties_.at(jobIdxTop)
                };
                minDiffCurrDay.at(jobIdx) = std::min(
                    minDiffCurrDay.at(jobIdx),
                    minDiffCurrDay.at(jobIdxTop) + diffIncr
                );
            }
            if(!stckJobIdxs.empty()) {
                minDiffCurrDay.at(jobIdx) = std::min(
                    minDiffCurrDay.at(jobIdx),
                    minDiffCurrDay.at(stckJobIdxs.top())
                );
            }
            stckJobIdxs.emplace(jobIdx);
        }
        minDiffPrevDay = minDiffCurrDay;
        rngs::fill(minDiffCurrDay, kMaxjobDifficulties_);
    }
    auto const minJobScheduleDifficulty{minDiffPrevDay.at(jobsSz - 1)};
    return minJobScheduleDifficulty;
}
