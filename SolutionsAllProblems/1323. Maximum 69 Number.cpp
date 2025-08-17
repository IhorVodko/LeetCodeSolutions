// problem : https://leetcode.com/problems/maximum-69-number/description/
// submission : https://leetcode.com/problems/maximum-69-number/submissions/1738586706
// solution post : https://leetcode.com/problems/maximum-69-number/solutions/7092489
//    /c-modern-readable-code-beats-100-runtime-zm9l

// #include <string>

class Solution {
public:
// let 'n' be a given number
// time complexity O(log10(n))
// space complexity O(log10(n))
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    int maximum69Number(int const num_) const; 
};

int Solution::maximum69Number(int const num_) const {
    auto numStr{std::to_string(num_)};
    auto const firstSix{numStr.find('6')};
    if(firstSix == std::string::npos) {
        return num_;
    }
    numStr.at(firstSix) = '9';
    auto const num{std::stoi(numStr)};
    return num;
}
