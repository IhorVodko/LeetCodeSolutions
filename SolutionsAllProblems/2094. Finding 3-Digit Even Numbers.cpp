// problem : https://leetcode.com/problems/finding-3-digit-even-numbers/description/
// submission : https://leetcode.com/problems/finding-3-digit-even-numbers/submissions/1632210132
// solution post : https://leetcode.com/problems/finding-3-digit-even-numbers/solutions/6738656/
//    c-modern-readable-code-beats-100-by-cybe-ngsp

// #include <vector>

class Solution {
public:
// let 'n' be a length of the given array
// time complexity O(max(n, 10^3)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    std::vector<int> findEvenNumbers(std::vector<int> const & digits_) const;
};

std::vector<int> Solution::findEvenNumbers(
    std::vector<int> const & digits_
) const {
    auto dsCounts{std::vector<size_t>(10, 0)};
    for(auto const digit: digits_) {
        ++dsCounts.at(digit);
    }
    auto nums{std::vector<int>{}};
    auto const begin{dsCounts.begin()};
    auto const end{dsCounts.end()};
    for(auto c1{begin + 1}; c1 < end; ++c1) {
        if(*c1 == 0) { continue; }
        --*c1;
        for(auto c2{begin}; c2 < end; ++c2) {
            if(*c2 == 0) { continue; }
            --*c2;
            for(auto c3{begin}; c3 < end; c3 += 2) {
                if(*c3 == 0) { continue; }
                nums.emplace_back(
                    100 * (c1 - begin) + 10 * (c2 - begin) + (c3 - begin));
            }
            ++*c2;
        }
        ++*c1;
    }
    return nums;
}
