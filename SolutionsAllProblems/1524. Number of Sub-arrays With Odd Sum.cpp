// problem : https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/description/
// submission : https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/submissions/1555357370
// solution post : https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/solutions/6467741/
//     c-modern-readable-code-beats-100-runtime-4fbj

// #include <vector>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
namespace Constants {
    auto constexpr modVal{static_cast<int>(1e9 + 7)};
}

class Solution {
public:
    int numOfSubarrays(std::vector<int> const & nums) const {
        using namespace Constants;
        auto oddSumsTotal{0};
        auto prefixSum{0};
        auto oddSumsSeenBefore{0};
        auto evenSumsSeenBefore{1};
        for(auto const num: nums) {
            prefixSum = (prefixSum + num) % 2;
            if(prefixSum == 0) {
                oddSumsTotal += oddSumsSeenBefore;
                ++evenSumsSeenBefore;
            } else {
                oddSumsTotal += evenSumsSeenBefore;
                ++oddSumsSeenBefore;
            }
            oddSumsTotal %= modVal;
        }
        return oddSumsTotal;
    }
};
