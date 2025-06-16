// problem : https://leetcode.com/problems/max-difference-you-can-get-from-changing-an-integer/description/
// submission : https://leetcode.com/problems/max-difference-you-can-get-from-changing-an-integer/submissions/1665958402
// solution post : https://leetcode.com/problems/max-difference-you-can-get-from-changing-an-integer/solutions/6850239/
//    c-modern-readable-code-beats-100-runtime-y3os

// #include <ranges>
// #include <string>

class Solution {
public:
// let 'n' be a given number
// time complexity O(log10(n))
// space complexity O(log10(n))
// runtime 0 ms, beats 100.00 %
    int maxDiff(int const num_) const;
};

int Solution::maxDiff(int const num_) const {
    using std::ranges::replace;
    auto numMinStr{std::to_string(num_)};
    if(numMinStr.at(0) == '1') {
        if(auto const posOfchrToZero(numMinStr.find_first_not_of("01"));
            posOfchrToZero != std::string::npos
        ) {
            auto const chrToZero{numMinStr.at(posOfchrToZero)};
            replace(numMinStr, chrToZero, '0');
        }
    } else {
       auto const chrToOne{numMinStr.at(0)}; 
       replace(numMinStr, chrToOne, '1'); 
    }
    auto numMaxStr{std::to_string(num_)};
    if(auto const posOfchrToNine{numMaxStr.find_first_not_of('9')};
        posOfchrToNine != std::string::npos
    ) {
        auto const chrToNine{numMaxStr.at(posOfchrToNine)}; 
        replace(numMaxStr, chrToNine, '9');
    }
    auto const diffMax{std::stoi(numMaxStr) - std::stoi(numMinStr)};
    return diffMax;
}
