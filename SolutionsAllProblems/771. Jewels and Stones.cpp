// problem : https://leetcode.com/problems/jewels-and-stones/description/
// submission : https://leetcode.com/problems/jewels-and-stones/submissions/1503246124
// solution post : https://leetcode.com/problems/jewels-and-stones/solutions/6256692/c-modern-readable-code-beats-100-runtime-gl68

// #include <algorithm>
// #include <string>
// #include <unordered_set>

// let 'j' be a parameter 'jewels' length
// 's' - parameter 'stones' length
// time complexity O(j + s)
// space complexity O(j)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int numJewelsInStones(
        std::string const & jewels,
        std::string const & stones
    ) const {
        auto jewelsSet{std::unordered_set<char>{jewels.begin(), jewels.end()}};    
        return std::count_if(stones.begin(), stones.end(), [&]
            (auto const stone) { return jewels.contains(stone); });
    }
};
