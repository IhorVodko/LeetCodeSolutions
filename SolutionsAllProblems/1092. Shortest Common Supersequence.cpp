// problem : https://leetcode.com/problems/shortest-common-supersequence/description/
// submission : https://leetcode.com/problems/shortest-common-supersequence/submissions/1558531674
// solution post : https://leetcode.com/problems/shortest-common-supersequence/solutions/6478759/
//     c-modern-readable-code-beats-100-runtime-7dbo

// #include <algorithm,>
// #include <array>
// #include <string>

namespace Utility {
    auto static sDp{std::array<std::array<int, 1'001>, 1'001>{}};
}

// let 's1' be a length of the given first string
// 's2' - of the second string
// time complexity O(s1 * s2)
// space complexity O(s1 * s2)
// runtime 7 ms, beats 99.96 %
class Solution {
public:
    std::string shortestCommonSupersequence(
        std::string const & str1,
        std::string const & str2
    ) const {
        BuildDpTable(str1, str2);
        return RecostructScs(str1, str2);     
    }
private:
    void BuildDpTable(
        std::string const & str1,
        std::string const & str2
    ) const {
        using namespace Utility;
        auto const str1Length{str1.size()};    
        auto const str2Length{str2.size()};
        for(auto row{0}; row <= str1Length; ++row) {
            sDp[row][0] = row;
        }
        for(auto col{0}; col < str2Length; ++col) {
            sDp[0][col] = col;
        }
        for(auto row{1}; row <= str1Length; ++row) {
            for(auto col{1}; col <= str2Length; ++col) {
                if(str1[row - 1] == str2[col - 1]) {
                    sDp[row][col] = sDp[row - 1][col - 1] + 1;
                } else {
                    sDp[row][col] = std::min(sDp[row - 1][col],
                        sDp[row][col - 1]) + 1;
                }
            }
        }
    }
    std::string RecostructScs(
        std::string const & str1,
        std::string const & str2
    ) const {
        using namespace Utility;
        auto const str1Length{str1.size()};    
        auto const str2Length{str2.size()};
        auto scs{std::string{}};
        auto row{str1Length};
        auto col{str2Length};
        while(row > 0 && col > 0) {
            if(str1[row - 1] == str2[col - 1]) {
                scs += str1[row - 1];
                --row;
                --col;
            } else if(sDp[row - 1][col] < sDp[row][col - 1]) {
                scs += str1[row - 1];
                --row;
            } else {
                scs += str2[col - 1];
                --col;
            }
        }
        while(row > 0) {
            scs += str1[row - 1];
            --row;
        }
        while(col > 0) {
            scs += str2[col - 1];
            --col;
        }
        std::reverse(scs.begin(), scs.end());
        return scs;
    }
};
