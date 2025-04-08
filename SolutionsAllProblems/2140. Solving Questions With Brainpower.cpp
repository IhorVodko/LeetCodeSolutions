// problem : https://leetcode.com/problems/solving-questions-with-brainpower/description/
// submission : https://leetcode.com/problems/solving-questions-with-brainpower/submissions/1600598253
// solution post : https://leetcode.com/problems/solving-questions-with-brainpower/solutions/6629234/
//     c-modern-readable-code-beats-100-runtime-pbtn

// #include <algorithm>
// #include <vector>

// let 'n' be a count of questions given
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using Arr2T = std::vector<std::vector<int>>; 
    long long mostPoints(Arr2T const & questions_) const {
        auto const questionsCount{questions_.size()};
        auto dp{std::vector<long long>(questionsCount, 0)};
        dp.back() = questions_.back().front();
        for(auto i{questionsCount - 2}; i + 1 >= 1; --i) {
            dp[i] = questions_[i][0];
            auto const skipCount{questions_[i][1]};
            if(i + skipCount + 1 < questionsCount) {
                dp[i] += dp[i + skipCount + 1];
            }
            dp[i] = std::max(dp[i], dp[i + 1]);
        } 
        return dp.front();
    }
};
