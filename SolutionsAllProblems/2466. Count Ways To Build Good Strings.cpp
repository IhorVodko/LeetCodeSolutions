// problem : https://leetcode.com/problems/count-ways-to-build-good-strings/description/
// submission : https://leetcode.com/problems/count-ways-to-build-good-strings/submissions/1493516137
// solution post : https://leetcode.com/problems/count-ways-to-build-good-strings/solutions/6210239/c-modern-readable-code-optimal-time-comp-ne0g

// #include <vector>

// let 'n' be a parameter 'high' value
// time complexity O(n)
// space complexity O(n)
// runtime 4 ms, beats 78.17 %
namespace Utility {
    auto constexpr mod{1'000'000'007};
}

class Solution {
public:
    int countGoodStrings(
        int const low,
        int const high,
        int const zero,
        int const one
    ) const {
        using Utility::mod;
        auto goodStrsCount{std::vector<int>(high + 1, 0)};
        goodStrsCount.at(0) = 1;
        auto begin{goodStrsCount.cbegin()};
        for(auto count{goodStrsCount.begin() + 1}, end{goodStrsCount.end()};
            count < end; ++count
        ) {
            if(count - zero >= begin) {
                *count += *(count - zero);
            }
            if(count - one >= begin) {
                *count += *(count - one);
            }
            *count %= mod;
        }
        return std::accumulate(begin + low, begin + high + 1, 0L) % mod;
    }
};
