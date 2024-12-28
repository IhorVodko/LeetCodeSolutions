// problem : https://leetcode.com/problems/group-anagrams/description/
// submission : https://leetcode.com/problems/group-anagrams/submissions/1490691714
// solution post : https://leetcode.com/problems/group-anagrams/solutions/6197728/c-modern-readable-code-beats-99-runtime-1ropf

// #include <algorithm>
// #icnlude <string>
// #incldue <vector>
// #include <unordered_map>

// let 'n' be a parameter 'strs' length
// 's' - longest string length of strings at 'strs'
// time complexity O(n * s * log(s))
// space complexity O(n * s)
// runtime 7 ms, beats 99.36 %
class Solution {
public:
    using GroupOfAnagramsT = std::vector<std::string>;
    using GroupOfAnagramsItsT = std::vector<GroupOfAnagramsT::iterator>;
    std::vector<GroupOfAnagramsT> groupAnagrams(
        std::vector<std::string> & strs
    ) const {
        auto strToAnagrams{std::unordered_map<std::string,
            GroupOfAnagramsItsT>{}};
        for(auto str{strs.begin()}, end{strs.end()}; str < end; ++str) {
            strToAnagrams[ToKey(*str)].emplace_back(str);
        }
        auto groupsOfAnagrams{std::vector<GroupOfAnagramsT>{}};
        groupsOfAnagrams.reserve(strToAnagrams.size());
        for(auto const & [_, groupOfAnagrams]: strToAnagrams) {
            groupsOfAnagrams.emplace_back(GroupOfAnagramsT{});
            for(auto anagramIt : groupOfAnagrams) {
                groupsOfAnagrams.back().emplace_back(std::move(*anagramIt));
            }
        }
        return groupsOfAnagrams;

    }
private:
    std::string ToKey(std::string str) const {
        std:sort(str.begin(), str.end()); 
        return str;
    }
};
