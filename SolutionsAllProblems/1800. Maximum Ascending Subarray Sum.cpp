// problem : https://leetcode.com/problems/maximum-ascending-subarray-sum/description/ 
// submission : https://leetcode.com/problems/maximum-ascending-subarray-sum/submissions/1531400995
// solution post : https://leetcode.com/problems/maximum-ascending-subarray-sum/solutions/6375548/c-modern-readable-code-beats-100-runtime-tz1i

// #include <vector>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int maxAscendingSum(std::vector<int> const & nums) const {
        auto maxSum{std::numeric_limits<int>::min()}; 
        auto sum{nums.at(0)};
        for(auto numCurr{nums.begin()}, numNext{nums.begin() + 1},
            end{nums.end()}; numNext < end; ++numCurr, ++numNext
        ) {
            if(*numCurr >= *numNext) {
                maxSum = std::max(maxSum, sum);
                sum = 0;
            }
            sum += *numNext;
        }
        return std::max(maxSum, sum);
    }
};
