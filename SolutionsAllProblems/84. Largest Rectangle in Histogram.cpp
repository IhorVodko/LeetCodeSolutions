// problem : https://leetcode.com/problems/largest-rectangle-in-histogram/description/
// submission : https://leetcode.com/problems/largest-rectangle-in-histogram/submissions/1751376344
// solution post : https://leetcode.com/problems/largest-rectangle-in-histogram/solutions/7131607/
//    c-modern-readable-code-optimal-time-comp-8pbs

// #include <algorithm>
// #include <ranges>
// #include <vector>

class Solution {
public:
// let 'n' be a count of the given heights
// time complexity O(n)
// space complexity O(n)
// runtime 38 ms, beats 18.13 %
    [[nodiscard]]
    int largestRectangleArea(std::vector<int> const & heights_);
private:
    void FindMaxArea(
        int & maxArea_,
        std::vector<int> const & heights_,
        int const currIdx_
    );
    std::stack<int> mIdxsOfNonDecrsHeights;
};

int Solution::largestRectangleArea(std::vector<int> const & heights_) {
    namespace views = std::views;
    mIdxsOfNonDecrsHeights = {};
    mIdxsOfNonDecrsHeights.emplace(-1);
    auto maxArea{0};
    auto hsSz{static_cast<int>(heights_.size())};
    for(auto const idx: views::iota(0, hsSz)) {
        while(
            !mIdxsOfNonDecrsHeights.empty() &&
            mIdxsOfNonDecrsHeights.top() != -1 &&
            heights_.at(mIdxsOfNonDecrsHeights.top()) >= heights_.at(idx)
        ) {
            FindMaxArea(maxArea, heights_, idx);
        }
        mIdxsOfNonDecrsHeights.emplace(idx);
    }
    while(
        !mIdxsOfNonDecrsHeights.empty() &&
        mIdxsOfNonDecrsHeights.top() != -1
    ) {
        FindMaxArea(maxArea, heights_, hsSz);
    }
    return maxArea;
}

void Solution::FindMaxArea(
    int & maxArea_,
    std::vector<int> const & heights_,
    int const currIdx_
) {
    auto const currHeight{heights_.at(mIdxsOfNonDecrsHeights.top())};
    mIdxsOfNonDecrsHeights.pop();
    auto const currWidth{currIdx_ - mIdxsOfNonDecrsHeights.top() - 1};
    auto const currArea{currHeight * currWidth};
    maxArea_ = std::max(maxArea_, currArea);
}
