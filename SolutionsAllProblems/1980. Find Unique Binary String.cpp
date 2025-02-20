// problem : https://leetcode.com/problems/find-unique-binary-string/description/
// submission : https://leetcode.com/problems/find-unique-binary-string/submissions/1550096833
// solution post : https://leetcode.com/problems/find-unique-binary-string/solutions/6448441/
//     c-modern-readable-code-beats-100-runtime-10ha

// #include <string>

// let 'n' be a length of the given binary string
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    std::string findDifferentBinaryString(
        std::vector<std::string> const & nums
    ) const {
        auto result{std::string{}};
        for(auto idx{0}; idx < nums.size(); ++idx) {
            auto const chr{nums.at(idx).at(idx)};
            result += chr == '0' ? '1' : '0';
        }
        return result;
    }
};
