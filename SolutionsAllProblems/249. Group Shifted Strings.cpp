// problem : https://leetcode.com/problems/group-shifted-strings/description/
// submission : https://leetcode.com/problems/group-shifted-strings/submissions/1491721248
// solution post : https://leetcode.com/problems/group-shifted-strings/solutions/6202103/c-modern-readable-code-beats-100-runtime-o34t

// #include <string>
// #include <vector>
// #include <unordered_map>

// let 's' be a parameter 'strs' length
// maxS - a maximum strting length at 'strs'
// time complexity O(s * maxS)
// space complexity O(s)
// runtime 0 ms, beats 100.00 %
namespace Utility{
    auto constexpr alphabetSize{26};
    auto constexpr alphabetStart{'a'};
}

class Solution {
public:
    using GroupOfStrsT = std::vector<std::string>;
    using GroupsOfStrsT = std::vector<GroupOfStrsT>;
    GroupsOfStrsT groupStrings(GroupOfStrsT & strs) const {
        auto strsToGroupsOfStrs{std::unordered_map<
            std::string, std::vector<GroupOfStrsT::iterator>>{}};
        for(auto str{strs.begin()}, strEnd{strs.end()}; str < strEnd;
            ++str
        ) {
            strsToGroupsOfStrs[ToHash(*str)].emplace_back(str);
        }
        std::cout << strsToGroupsOfStrs.size() << "\n";
        auto groupsOfStrs{GroupsOfStrsT{}};
        groupsOfStrs.reserve(strsToGroupsOfStrs.size());
        for(auto const & [_, groupsOfStrIts]: strsToGroupsOfStrs) {
            groupsOfStrs.push_back(GroupOfStrsT{});
            for(auto const str: groupsOfStrIts) {
                groupsOfStrs.back().emplace_back(std::move(*str));
            }
        }
        return groupsOfStrs;
    }
private:
    std::string ToHash(std::string const & str) const {
        using Utility::alphabetSize;
        using Utility::alphabetStart;
        auto hashVal{std::string{}};
        for(auto chr{str.cbegin() + 1}, chrEnd{str.cend()}; chr < chrEnd;
            ++chr
        ) {
            hashVal += (*chr - *(chr - 1) + alphabetSize) % alphabetSize +
                alphabetStart;       
        }
        return hashVal;
    }
};
