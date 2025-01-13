// problem : https://leetcode.com/problems/minimum-length-of-string-after-operations/description/
// submission : https://leetcode.com/problems/minimum-length-of-string-after-operations/submissions/1507568440
// solution post : https://leetcode.com/problems/minimum-length-of-string-after-operations/solutions/6275488/c-modern-readable-code-beats-94-runtime-8fwdn

// #include <algorithm>
// #include <string>
// #include <vector>

namespace Utility {
    auto constexpr alphabetSize{26};
    auto constexpr alphabetStart{'a'};
}

// let 'n' be a parameter 'str' length
// time complexity O(n)
// space complexity O(1)
// runtime 7 ms, beats 93.55 %

class Solution {
public:
    int minimumLength(std::string const & str) const {
        using namespace Utility;
        auto chrCounts{std::vector< size_t>(alphabetSize, 0)};
        for(auto const chr: str) {
            ++chrCounts.at(chr - alphabetStart);
        }
        return std::accumulate(chrCounts.cbegin(), chrCounts.cend(), 0,
            [] (
                auto init,
                auto const chrCount
            ) {
                return init + (chrCount >= 3 ? chrCount % 2 ? 1 : 2 :
                    chrCount);
        });
    }
};
