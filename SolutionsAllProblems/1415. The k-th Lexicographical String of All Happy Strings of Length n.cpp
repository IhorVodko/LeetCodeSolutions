// problem : https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/
//     description/
// submission : https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/
//     submissions/1548901074
// solution post : https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/solutions/6443689/
//     c-modern-readable-code-beats-100-runtime-jquv

// #include <cmath>
// #include <string>
// #include <unordered_map>

namespace Utility{
    auto const nextSamllestChar{std::unordered_map<char, char>{
        {'a', 'b'}, {'b', 'a'}, {'c', 'a'}}};
    auto const nextGreatestChar{std::unordered_map<char, char>{
        {'a', 'c'}, {'b', 'c'}, {'c', 'b'}}};
}

// let 'n' be a length of a happy string
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    std::string getHappyString(
        int const happyStrLength,
        int happyStrIdx
    ) const {
        using namespace Utility;
        auto const delta{static_cast<int>(std::pow(2, happyStrLength - 1))};
        auto maxHappyStringsCount{3 * delta};
        if(happyStrIdx > maxHappyStringsCount) {
            return "";
        } 
        auto resultStr{std::string(happyStrLength, 'a')};
        auto startA{1};
        auto startB{startA + delta};
        auto startC{startB + delta};
        if(happyStrIdx < startB) {
            resultStr.at(0) = 'a';
            happyStrIdx -= startA;
        } else if(happyStrIdx < startC) {
            resultStr.at(0) = 'b';
            happyStrIdx -= startB;
        } else {
            resultStr.at(0) = 'c'; 
            happyStrIdx -= startC;
        }
        for(auto charIdx{1}; charIdx < happyStrLength; ++charIdx) {
            auto midpointGoupIdx{static_cast<int>(std::pow(
                2, happyStrLength - charIdx - 1))};
            if(happyStrIdx < midpointGoupIdx) {
                resultStr.at(charIdx) = nextSamllestChar.at(resultStr.at(
                    charIdx - 1));
            } else {
                resultStr.at(charIdx) = nextGreatestChar.at(resultStr.at(
                    charIdx - 1));
                happyStrIdx -= midpointGoupIdx;
            }
        }
        return resultStr;
    } 
};
