// problem : https://leetcode.com/problems/find-pivot-index/description/
// submission : https://leetcode.com/problems/find-pivot-index/submissions/1469505441
// solution post : https://leetcode.com/problems/find-pivot-index/solutions/6109996/c-modern-readable-code-beats-100-runtime

// #include <numeric>
// #include <vector>

class Solution {
public:
    // let 'n' be an input length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats  100.00 %
    int pivotIndex(
        std::vector<int> const & nums
    ) const {
        auto sum{std::accumulate(nums.cbegin(), nums.cend(), 0)};
        auto sumLeft{0};
        for(auto pivot{nums.cbegin()}, end{nums.cend() - 1}; pivot < end;
            ++pivot
        ) {
            if(2 * sumLeft == sum - *pivot) {
                return std::distance(nums.cbegin(), pivot);
            }
            sumLeft += *pivot;
        }
        return sumLeft == 0 ? nums.size() - 1 : -1;         
    }
};
