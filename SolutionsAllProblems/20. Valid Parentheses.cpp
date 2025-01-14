// problem : https://leetcode.com/problems/valid-parentheses/description/
// submission : https://leetcode.com/problems/valid-parentheses/submissions/1508633885
// solution post : https://leetcode.com/problems/valid-parentheses/solutions/6280730/c-modern-readable-code-beats-100-runtime-6ox9

// #include <stack>
// #include <string>
// #include <unordered_map>

// let 'n' be a parameter 'str' length
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    bool isValid(std::string const & str) const {
        auto chrs{std::stack<char>{}};
        for(auto const chr: str) {
            if(!closesToOpens.contains(chr)) {
                chrs.push(chr);
                continue;
            }
            if(!chrs.empty() && closesToOpens.at(chr) == chrs.top()) {
                chrs.pop();
            } else {
                return false;
            }
        }
        return chrs.empty(); 
    }
    Solution(): 
        closesToOpens{{')', '('}, {'}', '{'}, {']', '['}}
    {}
private:
    std::unordered_map<char, char> closesToOpens;
};
