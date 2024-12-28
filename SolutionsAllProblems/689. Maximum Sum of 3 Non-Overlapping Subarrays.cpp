// problem : https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/description/
// submission : https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/submissions/1491014672
// solution post : https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/solutions/6199092/c-modern-readable-code-beats-100-runtime-jaid 

// #include <algorithm>
// #include <vector>

// let 'n' be a parameter 'nums' length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    std::vector<int> maxSumOfThreeSubarrays(
        std::vector<int> const & nums,
        int const windowLength
    ) const {
        auto bestSingleStartIdx{0};
        auto bestDoubleStartIdx{std::vector<int>{0, windowLength}};
        auto const doubleWindowLength{windowLength * 2};
        auto bestTripleStartIdx{std::vector<int>{
            0, windowLength, doubleWindowLength}};
        auto const begin{nums.cbegin()};
        auto currentSingleWindowSum{Sum(begin, windowLength)};
        auto currentWindowDoubleSum{Sum(begin, doubleWindowLength)};
        auto currentWindowTripleSum{Sum(begin, windowLength * 3)};
        auto bestSingleSum{currentSingleWindowSum};
        auto bestDoubleSum{bestSingleSum + currentWindowDoubleSum};
        auto bestTripleSum{bestDoubleSum + currentWindowTripleSum};
        for(auto singleStartIndex{1}, doubleStartIndex{windowLength + 1},
            tripleStartIndex{doubleWindowLength + 1};
            tripleStartIndex <= nums.size() - windowLength; ++singleStartIndex,
            ++doubleStartIndex, ++tripleStartIndex
        ) {
            currentSingleWindowSum += -nums.at(singleStartIndex - 1) +
                nums.at(singleStartIndex + windowLength - 1);
            currentWindowDoubleSum +=  -nums.at(doubleStartIndex - 1) +
                nums.at(doubleStartIndex + windowLength - 1);
            currentWindowTripleSum +=  -nums.at(tripleStartIndex - 1) +
                nums.at(tripleStartIndex + windowLength - 1);
            if(currentSingleWindowSum > bestSingleSum) {
                bestSingleStartIdx = singleStartIndex;
                bestSingleSum = currentSingleWindowSum;
            }
            if(currentWindowDoubleSum + bestSingleSum > bestDoubleSum) {
                bestDoubleStartIdx.assign({bestSingleStartIdx, doubleStartIndex});
                bestDoubleSum = currentWindowDoubleSum + bestSingleSum;
            }
            if(currentWindowTripleSum + bestDoubleSum > bestTripleSum) {
                std::copy(bestDoubleStartIdx.cbegin(),
                    bestDoubleStartIdx.cend(), bestTripleStartIdx.begin());
                bestTripleStartIdx.back() = tripleStartIndex;
                bestTripleSum = currentWindowTripleSum + bestDoubleSum;
            }
        } 
        return bestTripleStartIdx;
    }
private:
    int Sum(
        auto const first,
        auto const length
    ) const {
        return std::accumulate(first, first + length, 0);
    }
};
