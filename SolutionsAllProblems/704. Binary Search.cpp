// problem : https://leetcode.com/problems/binary-search/description/
// submission : https://leetcode.com/problems/binary-search/submissions/1614911900
// solution post : https://leetcode.com/problems/binary-search/solutions/6678127/
//     c-modern-readable-code-beats-100-runtime-irp9

// #include <vector>

// let 'n' be a count of the given numbers
// time complexity O(log(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int search(
        std::vector<int> & nums_,
        int const targetNum_
    ) const;
};

int Solution::search(
    std::vector<int> & nums_,
    int const targetNum_
) const {
    for(auto leftNumIt{nums_.begin()}, rightNumIt{nums_.end() - 1},
        midNumIt{nums_.begin() + ((rightNumIt - leftNumIt) / 2)};
        leftNumIt <= rightNumIt;
    ) {
        if(targetNum_ == *midNumIt) {
            return midNumIt - nums_.begin();
        } else if(targetNum_ < *midNumIt ) {
            rightNumIt = midNumIt - 1;
            midNumIt = leftNumIt + (rightNumIt - leftNumIt) / 2;
        } else {
            leftNumIt = midNumIt + 1;
            midNumIt = leftNumIt + (rightNumIt - leftNumIt) / 2;
        }
    }
    return -1;
}
