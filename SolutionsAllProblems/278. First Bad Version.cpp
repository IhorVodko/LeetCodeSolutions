// problem : https://leetcode.com/problems/first-bad-version/submissions/1622961393/
// submission : https://leetcode.com/problems/first-bad-version/submissions/1622961393
// solution post : https://leetcode.com/problems/first-bad-version/solutions/6705521/
//    c-modern-readable-code-beats-100-runtime-75yd

// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
// let 'n' be a given version
// time complexity O(log(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    int firstBadVersion(int const versionMax_) const;
};

int Solution::firstBadVersion(int const versionMax_) const {
    auto mid{1 + (versionMax_ - 1) / 2};
    for(auto left{1}, right{versionMax_}; left < right;
        mid = left + (right - left) / 2
    ) {
        auto const isBadCurr{::isBadVersion(mid)};
        if(isBadCurr) {
            right = mid; 
        } else {
            left = mid + 1;
        }
    }
    return mid;
}
