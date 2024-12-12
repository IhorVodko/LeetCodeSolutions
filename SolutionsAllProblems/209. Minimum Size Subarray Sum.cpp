// problem : https://leetcode.com/problems/minimum-size-subarray-sum/description/
// submission : https://leetcode.com/problems/minimum-size-subarray-sum/submissions/1477253377
// solution post : https://leetcode.com/problems/minimum-size-subarray-sum/solutions/6140571/c-modern-readable-code-beats-100-runtime


// #include <algorithm>
// #include <iterator>
// #include <vector>


class Solution {
public:
    // let 'n' be a parameter 'nums' length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    int minSubArrayLen(
        int const target,
        std::vector<int> & nums
    ) const {
        auto lengthMin{static_cast<long>(nums.size() + 1)};
        auto sum{0};
        for(auto first{nums.cbegin()}, last{nums.cbegin()}, end{nums.cend()};
            last < end; ++last
        ) {
            if((sum += *last) < target) {
                continue;
            }
            lengthMin = std::min(lengthMin, std::distance(first, last) + 1);
            (sum -= *last--) -= *first++;
        }
        return lengthMin > nums.size() ? 0 : lengthMin;
    }
};
