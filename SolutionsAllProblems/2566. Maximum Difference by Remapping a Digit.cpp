// problem : https://leetcode.com/problems/maximum-difference-by-remapping-a-digit/description/
// submission : https://leetcode.com/problems/maximum-difference-by-remapping-a-digit/submissions/1664027260
// solution post : https://leetcode.com/problems/maximum-difference-by-remapping-a-digit/solutions/6843560/
//    c-modern-readable-code-beats-100-runtime-kg0q

// #include <string>

class Solution {
public:
// let 'n' be a given number
// time complexity O(log10(n))
// space complexity O(log10(n))
// runtime 0 ms, beats 100.00 %
    int minMaxDifference(int const num_) const;
};

int Solution::minMaxDifference(int const num_) const {
    auto numMinStr{std::to_string(num_)};
    auto numMaxStr{numMinStr};
    auto oldChr{numMinStr.at(0)};
    std::replace(numMinStr.begin(), numMinStr.end(), oldChr, '0');
    auto const firstNotNineIdx{numMaxStr.find_first_not_of('9')};
    if(firstNotNineIdx != std::string::npos) {
        oldChr = numMaxStr.at(firstNotNineIdx);
        std::replace(numMaxStr.begin(), numMaxStr.end(), oldChr, '9');
    }
    auto const diffMax{std::stoi(numMaxStr) - std::stoi(numMinStr)};
    return diffMax;
}
