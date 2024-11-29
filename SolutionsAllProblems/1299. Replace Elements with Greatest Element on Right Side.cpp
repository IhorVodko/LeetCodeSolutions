// problem : https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/
// submission : https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/submissions/1465699066
// solution post: https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/solutions/6094212/c-modern-readable-code-beats-100-runtime

// #include <algorithm>
// #include <vector>

class Solution{
public:
    // let 'n' be an input length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    // memory 72.7 mb, beats 16.44 %
    std::vector<int> replaceElements(
        std::vector<int> & arr
    ) {
        constexpr auto rangeMin{int(1)}; 
        if(arr.size() == 1) {
            arr.front() = -1;
            return arr;
        }
        auto max{arr.back()};
        auto memorize{arr.back()};
        for(auto num{arr.rbegin() + 1}, end{arr.rend()}; num < end; ++num) {
            memorize = *num;
            *num = max;
            max = std::max(memorize, max);
        }
        arr.back() = -1;
        return arr; 
    }
};
