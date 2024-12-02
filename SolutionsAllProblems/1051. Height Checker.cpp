// problem : https://leetcode.com/problems/height-checker/description/
// submission : https://leetcode.com/problems/height-checker/submissions/1468580566
// solution post: https://leetcode.com/problems/height-checker/solutions/6105823/c-modern-readable-code-beats-100-runtime

// #include <algorithm>
// #include <functional>
// #include <numeric>
// #include <vector>


class Solution{
public:
    // let 'n' be an input size
    // time complexity O(nlog(n))
    // space complexity O(n)
    // runtime 0 ms, beats 100.00 %
    int heightChecker(std::vector<int> const & heights) const {
        auto copyH{heights};
        std::sort(copyH.begin(), copyH.end());
        return std::inner_product(heights.cbegin(), heights.cend(),
            copyH.begin(), 0, std::plus<>(), std::not_equal_to<>());
    }
};
