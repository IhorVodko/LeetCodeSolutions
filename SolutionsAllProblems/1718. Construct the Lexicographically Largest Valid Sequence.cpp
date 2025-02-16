// problem : https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/description/
// submission : https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/submissions/1545267978
// solution post : https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/solutions/6430295/c-modern-readable-code-beats-100-runtime-tr3x

// #include <vector>

// let 'n' be a given number value
// time complexity O(n!)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    std::vector<int> constructDistancedSequence(int const targetNum) const {
        auto resultSeq{std::vector<int>(targetNum * 2 - 1, 0)};
        auto isNumUsed{std::vector<bool>(targetNum + 1, false)};
        findLexLargestSeq(resultSeq, isNumUsed, 0, targetNum);
        return resultSeq;
    }
private:
    bool findLexLargestSeq(
        std::vector<int> & resultSeq,
        std::vector<bool> & isNumUsed,
        int const currIdx,
        int const targetNum
    ) const {
        if(currIdx == resultSeq.size()) {
            return true;
        }
        if(resultSeq.at(currIdx) != 0) {
            return findLexLargestSeq(resultSeq, isNumUsed, currIdx + 1,
                targetNum);
        }
        for(auto numToPlace{targetNum}; numToPlace >= 1; --numToPlace) {
            if(isNumUsed.at(numToPlace)) {
                continue;
            }
            isNumUsed.at(numToPlace) = true;
            resultSeq.at(currIdx) = numToPlace;
            if(numToPlace == 1) {
                if(findLexLargestSeq(resultSeq, isNumUsed, currIdx + 1,
                    targetNum)
                ) {
                    return true;
                }
            } else if(currIdx + numToPlace < resultSeq.size() &&
                resultSeq.at(currIdx + numToPlace) == 0
            ) {
                resultSeq.at(currIdx + numToPlace) = numToPlace;
                if(findLexLargestSeq(resultSeq, isNumUsed, currIdx + 1,
                    targetNum)
                ) {
                    return true;
                }
                resultSeq.at(currIdx + numToPlace) = 0;
            }
            resultSeq.at(currIdx) = 0;
            isNumUsed.at(numToPlace) = false;
        }
        return false;
    }
};
