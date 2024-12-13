// problem : https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/description/
// submission : https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/submissions/1477776988
// solution post : https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/solutions/6142768/c-modern-readable-code-by-cyberartist-87ot


// #include <algorithm>
// #include <vector>
// #include <utility>


class Solution {
public:
    // let 'n' be a parameter 'nums' length
    // time complexity O(n * log(n))
    // space complexity O(n)
    // runtime 49 ms, beats 98.19 %
    long long findScore(
        std::vector<int> & nums
    ) const {
        auto numsSorted{std::vector<std::pair<int, int>>{}};
        numsSorted.reserve(nums.size());
        for(auto idx{size_t{0}}; idx < nums.size(); ++idx) {
            numsSorted.emplace_back(nums.at(idx), idx);
        }
        std::sort(numsSorted.begin(), numsSorted.end());
        auto score{0LL};
        auto constexpr marked{0};
        for(auto numIdx{numsSorted.cbegin()}, end{numsSorted.cend()}; numIdx < end;
            ++numIdx
        ) {
            if(nums.at(numIdx->second) == marked) {
                continue;
            }
            score += numIdx->first;
            if(0 <= numIdx->second - 1) {
                nums.at(numIdx->second - 1) = marked;
            }
            if(numIdx->second + 1 < nums.size()) {
                nums.at(numIdx->second + 1) = marked;
            }
        }
        return score; 
    }
};
