// problem : https://leetcode.com/problems/closest-prime-numbers-in-range/description/
// submission : https://leetcode.com/problems/closest-prime-numbers-in-range/submissions/1566421264
// solution post : https://leetcode.com/problems/closest-prime-numbers-in-range/solutions/6510706/
//     c-modern-readable-code-optimal-time-comp-fct4

// #include <limits>
// #include <vector>

// let 'l' be a lower bound given
// 'u' - upper bound
// time complexity O(u * log((log(u))) + u - l)
// space complexity O(u)
// runtime 148 ms, beats 75.09 %
class Solution {
public:
    std::vector<int> closestPrimes(
        int const leftNum_,
        int const rightNum_
    ) const {
        auto sieveArr_{DoSieve(rightNum_)};
        auto primeNums{std::vector<int>{}};
        primeNums.reserve(rightNum_ / 2);
        for(auto num{leftNum_}; num <= rightNum_; ++num) {
            if(sieveArr_[num] == 1) {
                primeNums.emplace_back(num);
            }
        }
        if(primeNums.size() < 2) {
            return {-1, -1};
        }
        auto minDiff{std::numeric_limits<int>::max()};
        auto closestTwoPrimeNums{std::vector<int>{2, -1}};
        for(auto i{1}; i < primeNums.size(); ++i) {
            auto diff{primeNums[i] - primeNums[i - 1]};
            if(diff < minDiff) {
                minDiff = diff;
                closestTwoPrimeNums[0] = primeNums[i - 1];
                closestTwoPrimeNums[1] = primeNums[i];
            }
        }
        return closestTwoPrimeNums;

    }
private:
    std::vector<int> DoSieve(int const upperLimit_) const {
        auto sieveArr{std::vector<int>(upperLimit_ + 1, 1)};
        sieveArr.at(0) = sieveArr.at(1) = 0;
        for(auto num{2}; num * num <= upperLimit_; ++num) {
            if(sieveArr[num] == 1) {
                for(auto multiple{num * num}; multiple <= upperLimit_;
                    multiple += num
                ) {
                    sieveArr[multiple] = 0;        
                }
            }
        }
        return sieveArr;
    }
};
