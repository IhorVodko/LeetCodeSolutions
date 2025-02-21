// problem : https://leetcode.com/problems/decode-string/description/
// submission : https://leetcode.com/problems/decode-string/submissions/1550845942
// solution post : https://leetcode.com/problems/decode-string/solutions/6451578/
//     c-modern-readable-code-beats-100-runtime-njtg

// #include <stack>
// #include <string>

// let 's' be a length of the given string
// 'r' - maximum value of any substring repetiotion
// time complexity O(r * s)
// space complexity O(s)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    std::string decodeString(std::string const & str) const {
        auto stackCounts{std::stack<int>{}};
        auto stackStrs{std::stack<std::string>{}};
        auto decodedStr{std::string{}};
        auto counts{0};
        for(auto const chr: str) {
            if(std::isdigit(chr)) {
                counts = counts * 10 + chr - '0';
            } else if(chr == '[') {
                stackCounts.push(counts);
                stackStrs.push(std::move(decodedStr));
                decodedStr = {};
                counts = 0;
            } else if(chr == ']') {
                auto decodedPartStr{stackStrs.top()};
                stackStrs.pop();
                for(auto countsCurr{stackCounts.top()}; countsCurr > 0;
                    --countsCurr
                ) {
                    decodedPartStr += decodedStr;
                }
                stackCounts.pop();
                decodedStr = std::move(decodedPartStr);
            } else {
                decodedStr += chr;
            }
        }
        return decodedStr; 
    }
};
