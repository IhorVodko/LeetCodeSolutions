// problem : https://leetcode.com/problems/rabbits-in-forest/description/
// submission : https://leetcode.com/problems/rabbits-in-forest/submissions/1612895647
// solution post : https://leetcode.com/problems/rabbits-in-forest/solutions/6672112/
//    c-modern-readable-code-beats-100-runtime-tkd9

// #include <cmath>
// #include <vector>
// #include <unordered_map>

// let 'n' be a count of the given answers
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int numRabbits(std::vector<int> const & answers_) const {
        auto answerToCount{std::unordered_map<int, int>{}};
        for(auto const answer: answers_) {
            ++answerToCount[answer];
        }
        auto rabbitsCount{0};
        for(auto const [answer, count]: answerToCount) {
            rabbitsCount += (answer + 1) * std::ceil(count / (answer + 1.0));
        }
        return rabbitsCount;
    }

};
