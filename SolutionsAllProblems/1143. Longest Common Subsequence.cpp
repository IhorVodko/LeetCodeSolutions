// problem : https://leetcode.com/problems/longest-common-subsequence/
// submission : https://leetcode.com/problems/longest-common-subsequence/submissions/1789952384
// solution post : https://leetcode.com/problems/longest-common-subsequence/solutions/7244834/
//    c-modern-readable-code-optimal-time-comp-r8ny

// import std;

class Solution {
public:
// let 's1' be the length of the given first string
// 's2' - of the second given string
// time complexity O(s1 * s2)
// space complexity O(min(s1, s2))
// runtime 31 ms, beats 37.33 %
    [[nodiscard]]
    auto longestCommonSubsequence(
        std::string & str1_,
        std::string & str2_
    ) const -> int;

private:
    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
};

auto Solution::longestCommonSubsequence(
    std::string & str1_,
    std::string & str2_
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const str1Sz{std::ssize(str1_)};
    auto const str2Sz{std::ssize(str2_)};
    auto dpPrev{std::vector<int>(str2Sz)};
    auto dpCurr{std::vector<int>(str2Sz)};
    for(auto idx: vs::iota(0, str2Sz)) {
        auto const chr1{str1_.at(0)};
        auto const chr2{str2_.at(idx)};
        if(chr1 == chr2) {
            dpPrev.at(idx) = 1;
        } else if(idx > 0) {
            dpPrev.at(idx) = dpPrev.at(idx - 1);
        }
    }
    for(auto idx1: vs::iota(1, str1Sz)) {
        auto const chr1{str1_.at(idx1)};
        for(auto idx2: vs::iota(0, str2Sz)) {
            auto const chr2{str2_.at(idx2)};
            if(idx2 == 0) {
                dpCurr.at(idx2) = chr1 == chr2 ? 1 : dpPrev.at(idx2);
            } else {
                dpCurr.at(idx2) = std::max(
                    dpCurr.at(idx2 - 1),
                    chr1 == chr2 ?
                        dpPrev.at(idx2 - 1) + 1 :
                        dpPrev.at(idx2)
                );
            }    
        }
        dpPrev = dpCurr;
        rngs::fill(dpCurr, 0); 
    }
    auto const lcs{dpPrev.at(str2Sz - 1)};
    return lcs; 
}
