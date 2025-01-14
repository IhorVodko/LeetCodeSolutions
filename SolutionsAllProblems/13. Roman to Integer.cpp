// problem : https://leetcode.com/problems/roman-to-integer/description/
// submission : https://leetcode.com/problems/roman-to-integer/submissions/1508547064
// solution post : https://leetcode.com/problems/roman-to-integer/solutions/6280328/c-modern-readable-code-beats-100-runtime-qnfx

// #include <string>
// #include <unordered_map>

// let 'n' be a parameter 'str' length
// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int romanToInt(std::string const & str) const {
        if(str.size() == 1) {
            return symbolsToValues.at(str.at(0));
        }
        auto num{0};
        auto numPrev{0};
        auto numThis{0};
        auto step{0};
        for(auto chr{str.begin() + 1}, end{str.end()}; chr < end; chr += step
        ) {
            numPrev = symbolsToValues.at(*(chr - 1));
            numThis = symbolsToValues.at(*chr);
            if(numPrev >= numThis) {
                num += numPrev;
                step = 1;
            } else {
                num += numThis - numPrev;
                step = 2;
            }
            if(chr == end - 1 && step == 1) {
                num += numThis;
            } else if (chr == end - 2 && step == 2) {
                num += symbolsToValues.at(*(chr + 1));
            }
        }
        return num;
    }
private:
    static std::unordered_map<char, int> symbolsToValues;
};

std::unordered_map<char, int > Solution::symbolsToValues{{'I', 1}, {'V', 5},
    {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
