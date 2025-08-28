// problem : https://leetcode.com/problems/sort-matrix-by-diagonals/description/
// submission : https://leetcode.com/problems/sort-matrix-by-diagonals/submissions/1751418227
// solution post : https://leetcode.com/problems/sort-matrix-by-diagonals/solutions/7131747/
//    c-modern-readable-code-beats-100-runtime-3xtr

// #include <algorithm>
// #include <vector>

class Solution {
public:
    using mxT = std::vector<std::vector<int>>;
// let 'n' by 'n' be a size of the given maxtrix
// time complexity O(n^2 * log2(n))
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    mxT sortMatrix(mxT & mx_) const;
private:
    void SortLowerLeftTriangle(mxT & mx_) const;
    void SortUpperRightTriangle(mxT & mx_) const;
};

Solution::mxT Solution::sortMatrix(mxT & mx_) const {
    SortLowerLeftTriangle(mx_);
    SortUpperRightTriangle(mx_);
    return mx_;
}

void Solution::SortLowerLeftTriangle(mxT & mx_) const {
    namespace ranges = std::ranges;
    namespace views = std::views;
    auto const rcSz{std::ssize(mx_)};
    if(rcSz == 1) {
        return;
    }
    auto numsToSort{std::vector<int>{}};
    numsToSort.reserve(rcSz);
    for(auto const r: views::iota(0, rcSz)) {
        numsToSort.clear(); 
        auto nextR{r};
        auto nextC{0};
        do {
            numsToSort.emplace_back(mx_.at(nextR++).at(nextC++));
        } while (nextR < rcSz && nextC < rcSz);
        ranges::sort(numsToSort, std::greater{});
        nextR = r;
        nextC = 0;
        for(auto const num: numsToSort) {
            mx_.at(nextR++).at(nextC++) = num;
        } 
    }
}

void Solution::SortUpperRightTriangle(mxT & mx_) const {
    namespace ranges = std::ranges;
    namespace views = std::views;
    auto const rcSz{std::ssize(mx_)};
    if(rcSz == 1) {
        return;
    }
    auto numsToSort{std::vector<int>{}};
    numsToSort.reserve(rcSz);
    for(auto const c: views::iota(1, rcSz)) {
        numsToSort.clear(); 
        auto nextR{0};
        auto nextC{c};
        do {
            numsToSort.emplace_back(mx_.at(nextR++).at(nextC++));
        } while(nextR < rcSz && nextC < rcSz);
        ranges::sort(numsToSort); 
        nextR = 0;
        nextC = c;
        for(auto const num: numsToSort) {
            mx_.at(nextR++).at(nextC++) = num;
        }
    }
}
