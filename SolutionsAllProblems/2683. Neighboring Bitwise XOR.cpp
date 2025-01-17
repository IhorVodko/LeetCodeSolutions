// problem : https://leetcode.com/problems/neighboring-bitwise-xor/description/
// submission : https://leetcode.com/problems/neighboring-bitwise-xor/submissions/1511318678
// solution post : https://leetcode.com/problems/neighboring-bitwise-xor/solutions/6293403/c-modern-readable-code-beats-100-runtime-pq7h

// #include <algorithm>

// let 'n' be a parameter 'derived' length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %

class Solution {
public:
    bool doesValidArrayExist(std::vector<int> const & derived) const {
        return std::accumulate(derived.begin(), derived.end(), 0, [] (
                auto const init,
                auto const num
            ) {
                return init ^ num;
            }) == 0;
        }
};
