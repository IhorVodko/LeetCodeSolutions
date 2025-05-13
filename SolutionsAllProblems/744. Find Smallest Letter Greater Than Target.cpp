// problem : https://leetcode.com/problems/find-smallest-letter-greater-than-target/description/
// submission : https://leetcode.com/problems/find-smallest-letter-greater-than-target/submissions/1633115351
// solution post : https://leetcode.com/problems/find-smallest-letter-greater-than-target/solutions/6741723/
//    c-modern-readable-code-beats-100-by-cybe-opod/

class Solution {
public:
// let 'n' be a count of letters given
// time complexity O(log2(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    char nextGreatestLetter(
        std::vector<char> const & chrs_,
        char const target_
    ) const;
};

char Solution::nextGreatestLetter(
    std::vector<char> const & chrs_,
    char const target_
) const {
    auto const begin{chrs_.begin()};
    auto const end{chrs_.end()};
    auto mid{begin + ((end - 1) - begin) / 2};
    for(auto left{begin}, right{end - 1}; left < right;
        mid = left + (right - left) / 2
    ) {
        if(target_ < *mid) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return target_ < *mid ? *mid : chrs_.at(0);
}
