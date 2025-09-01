// problem : https://leetcode.com/problems/permutations/description/
// submission : https://leetcode.com/problems/permutations/submissions/1755922153
// solution post : https://leetcode.com/problems/permutations/solutions/7144987/
//  c-modern-readable-code-beats-100-runtime-xygo

// #include <algorithm>
// #include <ranges>
// #include <vector>

class Solution {
public:
    using numsT = std::vector<int>;
// let 'n' be a count of the given numbers
// time complexity O(n * n!)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    std::vector<numsT> permute(numsT & nums_);
private:
    void Backtrack(
        numsT & currNums_,
        numsT const & givenNums_
    );
    std::vector<numsT> mPermutations;
};

std::vector<Solution::numsT> Solution::permute(numsT & nums_) {
    namespace views = std::views;
    mPermutations.clear();
    auto const numsSz{nums_.size()};
    auto permutationsSz{1u};
    for(auto const num: views::iota(1u, numsSz)) {
        permutationsSz *= num;
    }
    mPermutations.reserve(permutationsSz);
    auto currNums{numsT{}};
    currNums.reserve(numsSz);
    Backtrack(currNums, nums_);
    return mPermutations;
}

void Solution::Backtrack(
    numsT & currNums_,
    numsT const & givenNums_
) {
    namespace ranges = std::ranges;
    auto const currSz{currNums_.size()};
    auto const givenSz{givenNums_.size()};
    if(currSz == givenSz) {
        mPermutations.emplace_back(currNums_);
    }
    for(auto const num: givenNums_) {
        if(ranges::find(currNums_, num) == currNums_.end()) {
            currNums_.emplace_back(num);
            Backtrack(currNums_, givenNums_);
            currNums_.pop_back();
        }
    }
}
