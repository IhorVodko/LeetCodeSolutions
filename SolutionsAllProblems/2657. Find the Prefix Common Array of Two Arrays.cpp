// problem : https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/description/
// submission : https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/submissions/1508723034
// solution post : https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/solutions/6281113/c-modern-readable-code-beats-100-runtime-ixbc

// #include <vector>

// let 'n' be a parameter 'A', 'B' lengthes
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    std::vector<int> findThePrefixCommonArray(
        std::vector<int> const & A,
        std::vector<int> const & B
    ) const {
        auto sz{A.size()};
        auto commonPrefLengthes{std::vector<int>(sz, 0)};
        auto numCounts{std::vector<size_t>(sz + 1, 0)};
        ++numCounts.at(A.at(0));
        ++numCounts.at(B.at(0));
        commonPrefLengthes.at(0) = numCounts.at(A.at(0)) == 2 ? 1 : 0;
        for(auto i{size_t{1}}; i < sz; ++i) {
            commonPrefLengthes.at(i) = commonPrefLengthes.at(i - 1);
            if(++numCounts.at(A.at(i)) == 2) {
                ++commonPrefLengthes.at(i);
            }
            if(++numCounts.at(B.at(i)) == 2) {
                ++commonPrefLengthes.at(i);
            }
        }
        return commonPrefLengthes;
    }
};
