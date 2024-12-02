// problem : https://leetcode.com/problems/find-numbers-with-even-number-of-digits/description/
// submission : https://leetcode.com/problems/find-numbers-with-even-number-of-digits/submissions/1463277372
// solution post: https://leetcode.com/problems/find-numbers-with-even-number-of-digits/solutions/6085226/c-modern-readable-code-beats-100-runtime

// #include <vector>
// #include <algorithm>


class Solution{
public:
    // let 'n' be an input length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100 %
    int findNumbers(std::vector<int> const & nums) const {
        return std::count_if(nums.cbegin(), nums.cend(), [&] (auto num) {
            return (10 <= num && num < 99) || (1000 <= num && num <= 9999) ||
                num == 100000;
        });
    }
};
