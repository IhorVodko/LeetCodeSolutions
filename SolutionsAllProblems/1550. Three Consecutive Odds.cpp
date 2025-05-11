// problem : https://leetcode.com/problems/three-consecutive-odds/description/
// submission : https://leetcode.com/problems/three-consecutive-odds/submissions/1631243530
// solution post : https://leetcode.com/problems/three-consecutive-odds/solutions/6735062/
//    c-modern-readable-code-beats-100-by-cybe-21i1

// #include <vector>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    bool threeConsecutiveOdds(std::vector<int> const & nums_) const;
};

bool Solution::threeConsecutiveOdds(std::vector<int> const & nums_) const {
    for(auto first{nums_.begin()}, last{nums_.begin()}, end{nums_.end()};
        last < end;
    ) {
        if(*last % 2 == 1) {
            if(last++ - first == 2) {
                return true;
            }
        } else {
            first = ++last;
        }
    }
    return false;
}
