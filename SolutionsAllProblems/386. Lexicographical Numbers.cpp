// problem :  https://leetcode.com/problems/lexicographical-numbers/description/
// submission : https://leetcode.com/problems/lexicographical-numbers/submissions/1658585714
// solution post : https://leetcode.com/problems/lexicographical-numbers/solutions/6826035/
//    c-modern-readable-code-beats-100-runtime-up5z

// #include <vector>

class Solution {
public:
// let 'n' be a count of numbers [1, given upper limit]
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    std::vector<int> lexicalOrder(int const upperLimit_) const;
};

std::vector<int> Solution::lexicalOrder(int const upperLimit_) const {
    auto numsSorted{std::vector<int>{}};
    auto numCurr{1};
    numsSorted.reserve(upperLimit_);
    for(auto numCount{0}; numCount < upperLimit_; ++numCount) {
        numsSorted.emplace_back(numCurr);
        if(numCurr * 10  <= upperLimit_) {
            numCurr *= 10;
        } else {
            while(numCurr % 10 == 9 || numCurr >= upperLimit_) {
                numCurr /= 10;
            }
            numCurr += 1;
        }
    }
    return numsSorted;
}
