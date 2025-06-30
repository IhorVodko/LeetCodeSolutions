// problem : https://leetcode.com/problems/find-subsequence-of-length-k-with-the-largest-sum/description
// submission : https://leetcode.com/problems/find-subsequence-of-length-k-with-the-largest-sum/submissions/1681487632
// solution post : https://leetcode.com/problems/find-subsequence-of-length-k-with-the-largest-sum/solutions/6903008/
//    c-modern-readable-code-beats-100-runtime-maid

// #include <limits>
// #include <ranges>
// #include <vector>

class Solution {
public:
    using intT = std::numeric_limits<int>;
    using numsT = std::vector<int>;
    using pqNumsValT = std::pair<int, size_t>;
    using pqNumsT = std::priority_queue<pqNumsValT, std::vector<pqNumsValT>,
        std::greater<>>;
    Solution();
// let 'n' be a count of the given numbers
// 's' - size of the required subsequence
// time complexity O(n * log2(s))
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    numsT maxSubsequence(
        numsT const & nums_,
        int const subseqSz_
    );
private:
    numsT DoCountingSortOfSelectedNums();
    std::function<bool(int const)> mIsNumSelected;
    pqNumsT mPqMinNums;
    size_t mNumsSz{};
};

Solution::Solution():
    mIsNumSelected{[] (int const num) { return num != intT::min(); }}
{}

Solution::numsT Solution::maxSubsequence(
    numsT const & nums_,
    int const subseqSz_
) {
    namespace views = std::views;
    namespace ranges = std::ranges;
    mNumsSz = nums_.size();
    mPqMinNums = {};
    mPqMinNums.emplace(nums_.at(0), 0);
    for(auto const idx: views::iota(1u, mNumsSz)) {
        auto const num{nums_.at(idx)};
        if(mPqMinNums.size() < subseqSz_) {
            mPqMinNums.emplace(num, idx);
        } else if(auto const numMin{mPqMinNums.top().first};
            num > numMin
        ) {
            mPqMinNums.pop();
            mPqMinNums.emplace(num, idx);
        }
    }
    auto numsSelectedSorted{DoCountingSortOfSelectedNums()};
    auto subseq{numsSelectedSorted |
        views::filter(mIsNumSelected) |
        ranges::to<numsT>()};
    return subseq;
}

Solution::numsT Solution::DoCountingSortOfSelectedNums() {
    auto numsSelected{numsT(mNumsSz, intT::min())};
    while(!mPqMinNums.empty()) {
        auto const [num, idx]{mPqMinNums.top()};
        mPqMinNums.pop();
        numsSelected.at(idx) = num;
    }
    return numsSelected;
}
