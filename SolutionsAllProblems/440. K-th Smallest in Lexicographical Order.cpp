// problem : https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/description/
// submission : https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/submissions/1658620527
// solution post : https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/solutions/6826148/
//    c-modern-readable-code-beats-100-runtime-luco

// #include <algorithm>

class Solution {
public:
// let 'n' be a count of numbers in [1, upper limit given]
// time complexity O(log10(n)^2)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    int findKthNumber(
        int const upperLimit_,
        int numMinKth_
    ) const;
private:
    int CountSteps(
        long prefixLow_,
        long const upperLimit_
    ) const;
};

int Solution::findKthNumber(
    int const upperLimit_,
    int numMinKth_
) const {
    auto numCurr{1};
    --numMinKth_;
    while(numMinKth_ > 0) {
        auto stepCount{CountSteps(numCurr, upperLimit_)};
        if(stepCount <= numMinKth_) {
            ++numCurr;
            numMinKth_ -= stepCount;
        } else {
            numCurr *= 10;
            --numMinKth_;
        }
    }
    return numCurr;
}

int Solution::CountSteps(
    long prefixLow_,
    long const upperLimit_
) const {
    auto stepCount{0};
    auto prefixHigh_{prefixLow_ + 1};
    while(prefixLow_ <= upperLimit_) {
        stepCount += std::min(upperLimit_ + 1, prefixHigh_) - prefixLow_;
        prefixLow_ *= 10;
        prefixHigh_ *= 10;
    }
    return stepCount;
}
