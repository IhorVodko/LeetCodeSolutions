// problem : https://leetcode.com/problems/construct-smallest-number-from-di-string/description/ 
// submission : https://leetcode.com/problems/construct-smallest-number-from-di-string/submissions/1547705341
// solution post : https://leetcode.com/problems/construct-smallest-number-from-di-string/solutions/6438983/
//     c-modern-readable-code-beats-100-runtime-rn9z

// #include <stack>
// #include <string>

// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    std::string smallestNumber(std::string const & pattern) const {
        auto result{std::string{}};
        auto nums{std::stack<int>{}};
        for(auto idx{0}; idx < pattern.size(); ++idx) {
            nums.push(idx + 1);
            if(pattern.at(idx) != 'I') {
                continue;
            }
            while(!nums.empty()) {
                result += std::to_string(nums.top());
                nums.pop();
            }
        }
        nums.push(pattern.size() + 1);
        while(!nums.empty()) {
            result += std::to_string(nums.top());
            nums.pop();
        }
        return result;
    }
};
