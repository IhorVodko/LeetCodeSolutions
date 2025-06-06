// problem : https://leetcode.com/problems/using-a-robot-to-print-the-lexicographically-smallest-string/description/
// submission : https://leetcode.com/problems/using-a-robot-to-print-the-lexicographically-smallest-string/submissions/
//    1655892334
// solution post : https://leetcode.com/problems/using-a-robot-to-print-the-lexicographically-smallest-string/solutions/
//    6817690/c-modern-readable-code-optimal-time-comp-w3kz

// #include <array>
// #include <stack>
// #include <string>

class Solution {
public:
// let 'n' be a length of the given string
// 'c' - size of the given character set
// time complexity O(n + c)
// space complexity O(n)
// runtime 83 ms, beats 28.22 %
    std::string robotWithString(std::string const & str_) const;
private:
    int ConvChrToInt(char const chr) const;
};

std::string Solution::robotWithString(std::string const & str_) const {
    auto chrCounts{std::array<int, 26>{}};
    chrCounts.fill(0);
    for(auto const chr: str_) {
        ++chrCounts.at(ConvChrToInt(chr));
    }
    auto chrsStack{std::stack<char>{}};
    auto strMin{std::string{}};
    auto chrMin{'a'};
    for(auto const chr: str_) {
        chrsStack.emplace(chr);
        --chrCounts.at(ConvChrToInt(chr));
        while(chrMin != 'z' && chrCounts.at(ConvChrToInt(chrMin)) == 0) {
            ++chrMin;
        }
        while(!chrsStack.empty() && chrsStack.top() <= chrMin) {
            strMin += chrsStack.top();
            chrsStack.pop();
        }
    }
    return strMin;
}

int Solution::ConvChrToInt(char const chr) const {
    auto const intAsChr{chr - 'a'};
    return intAsChr;
}
