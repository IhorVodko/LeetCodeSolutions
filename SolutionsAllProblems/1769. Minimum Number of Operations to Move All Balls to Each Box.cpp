// problem : https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/description/ 
// submission : https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/submissions/1499903822
// solution post : https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/solutions/6241239/c-modern-readable-code-beats-100-runtime-j3mu

// #include <string>
// #include <vector>

namespace Utility {
    auto constexpr isEmpty{'0'};
    auto constexpr notEmpty{'1'};
}

// let 'n' be a parameter 'boxes' length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    std::vector<int> minOperations(std::string const & boxes) const {
        using namespace Utility;
        auto minOps{std::vector<int>(boxes.size(), 0)};
        auto ballsCountRight{boxes.front() == isEmpty ? 0 : 1};
        for(auto idx{1Z}; idx < boxes.size(); ++idx) {
            if(boxes.at(idx) == notEmpty) {
                ++ballsCountRight;
                minOps.at(0) += idx;
            }
        }
        auto ballsCountLeft{0};
        for(auto idx{1Z}; idx < boxes.size(); ++idx) {
            minOps.at(idx) = minOps.at(idx - 1) +
                (boxes.at(idx - 1) == isEmpty ? ballsCountLeft - ballsCountRight :
                ++ballsCountLeft - --ballsCountRight);
        }
        return minOps;
    }
};
