// problem :  https://leetcode.com/problems/letter-tile-possibilities/description/
// submission : https://leetcode.com/problems/letter-tile-possibilities/submissions/1546340782
// solution post : https://leetcode.com/problems/letter-tile-possibilities/solutions/6433815/
//     c-modern-readable-code-beats-100-runtime-wobc

// #include <vector>

// let 'n' be a given string length
// time complexity O(2^n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int numTilePossibilities(std::string const & tiles) const {
        auto charCounts{CalculateCharCounts(tiles)};
        return FindAllSeqs(charCounts);
    }
private:
    std::vector<int> CalculateCharCounts(std::string const & str) const {
        auto charCounts{std::vector<int>(26, 0)};
        for(auto const chr: str) {
            ++charCounts.at(chr - 'A');
        }
        return charCounts;
    }
    int FindAllSeqs(std::vector<int> & charCounts) const {
        auto seqsCount{0};
        for(auto & chrCount: charCounts) {
            if(chrCount == 0) {
                continue;
            }
            ++seqsCount;
            --chrCount;
            seqsCount += FindAllSeqs(charCounts);
            ++chrCount;
        }
        return seqsCount;
    }
};
