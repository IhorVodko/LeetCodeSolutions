// problem : https://leetcode.com/problems/evaluate-reverse-polish-notation/description/
// submission : https://leetcode.com/problems/evaluate-reverse-polish-notation/submissions/1548646590
// solution post : https://leetcode.com/problems/evaluate-reverse-polish-notation/solutions/6442732/
//     c-modern-readable-code-beats-100-runtime-z0eo

// #include <stack>
// #include <string>
// #include <vector>
// #include <unordered_map>

namespace Utility {
    auto const operations{std::unordered_map<std::string,
        std::function<int(int, int)>>{
            {"*", [](int const num1, int const num2) {return num1 * num2;}},
            {"/", [](int const num1, int const num2) {return num1 / num2;}},
            {"+", [](int const num1, int const num2) {return num1 + num2;}},
            {"-", [](int const num1, int const num2) {return num1 - num2;}},
        }};
}

// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int evalRPN(std::vector<std::string> const & tokens) const {
        using namespace  Utility;
        auto stack{std::stack<int>{}}; 
        for(auto const token: tokens) {
            if(operations.contains(token)) {
                auto const num2{stack.top()};
                stack.pop();
                auto const num1{stack.top()};
                stack.pop();
                stack.push(operations.at(token)(num1, num2));
            } else {
                stack.push(std::stoi(token));
            }
        }
        return stack.top();
    }
};
