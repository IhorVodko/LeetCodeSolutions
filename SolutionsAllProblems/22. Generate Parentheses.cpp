// problem : https://leetcode.com/problems/generate-parentheses/description/
// submission : https://leetcode.com/problems/generate-parentheses/submissions/1739671064
// solution post : https://leetcode.com/problems/generate-parentheses/solutions/7095679/
//    c-modern-readable-code-beats-100-runtime-jkmm

// #include <ranges>
// #include <string>
// #include <vector>

class Solution {
public:
// let 'n' be a given count of pairs of parentheses
// time complexity O(4^n / sqrt(n)), Catalan number
// space complexity O(n) 
// runtime 0 ms, beats 100.00 %
    std::vector<std::string> generateParenthesis(
        int const pairsOfParansCount_
    );
private:
    void backtracking(
        int const leftCount_,
        int const rightCount_,
        int const pairsOfParansCount_
    );
    std::string mStartStr;
    std::vector<std::string> mValidCombs;
};

std::vector<std::string> Solution::generateParenthesis(
    int const pairsOfParansCount_
) {
    namespace views = std::views;
    mValidCombs.clear();
    mStartStr.clear();
    backtracking(0, 0, pairsOfParansCount_);
    return mValidCombs;
}

void Solution::backtracking(
    int const leftCount_,
    int const rightCount_,
    int const pairsOfParansCount_
) {
    if(mStartStr.size() == 2 * pairsOfParansCount_) {
        mValidCombs.emplace_back(mStartStr);
    }
    if(leftCount_ < pairsOfParansCount_) {
        mStartStr += '(';
        backtracking(leftCount_ + 1, rightCount_, pairsOfParansCount_);
        mStartStr.pop_back();
    } 
    if(leftCount_ > rightCount_) {
        mStartStr += ')';
        backtracking(leftCount_, rightCount_ + 1, pairsOfParansCount_);
        mStartStr.pop_back();
    } 
}
