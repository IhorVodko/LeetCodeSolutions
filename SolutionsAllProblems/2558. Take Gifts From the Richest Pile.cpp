// problem : https://leetcode.com/problems/take-gifts-from-the-richest-pile/description/
// submission : https://leetcode.com/problems/take-gifts-from-the-richest-pile/submissions/1477161820
// solution post : https://leetcode.com/problems/take-gifts-from-the-richest-pile/solutions/6140212/c-modern-readable-code-beats-100-runtime

// #include <functional>
// #include <priority_queue>
// #include <vector>

class Solution {
public:
    // let 'n' be a parameter 'gifts' length
    // 'm' - a parameter 'seconds'
    // time complexity O(n + m * log(n))
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    long long int pickGifts(
        std::vector<int> & gifts,
        int seconds
    ) const {
        auto heap{std::priority_queue{std::less(), std::move(gifts)}};
        while(seconds-- > 0) {
            heap.push(std::floor(std::sqrt(heap.top())));
            heap.pop();
        }
        auto sum{0LL};
        while(!heap.empty()) {
            sum += heap.top();
            heap.pop();
        }
        return sum;
    }
};
