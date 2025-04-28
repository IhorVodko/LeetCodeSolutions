// problem : https://leetcode.com/problems/count-subarrays-with-score-less-than-k/description/
// submission : https://leetcode.com/problems/count-subarrays-with-score-less-than-k/submissions/1620495976
// solution post : https://leetcode.com/problems/count-subarrays-with-score-less-than-k/solutions/6696517/
//     c-modern-readable-code-beats-100-runtime-82f6

// #include <vector>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    long long countSubarrays(
        std::vector<int> const & nums_,
        long long const limit_
    ) const;
};

long long Solution::countSubarrays(
    std::vector<int> const & nums_,
    long long const limit_
) const {
    auto subArrrsCount{0z};
    auto sum{static_cast<long long>(nums_.at(0))};
    for(auto first{nums_.begin()}, last{nums_.begin()}, end{nums_.end()};;) {
        if(first <= last && sum * (last - first + 1) >= limit_) {
            sum -= *first;
            ++first;
        } else {
            subArrrsCount += last - first + 1;
            ++last;
            if(last == end) {
                return subArrrsCount;
            }
            sum += *last;
        }
    }
    return -1;
}
