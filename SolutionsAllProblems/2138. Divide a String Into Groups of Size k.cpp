// problem : https://leetcode.com/problems/divide-a-string-into-groups-of-size-k/description/
// submission : https://leetcode.com/problems/divide-a-string-into-groups-of-size-k/submissions/1673806808
// solution post : https://leetcode.com/problems/divide-a-string-into-groups-of-size-k/solutions/6876834/
//    c-modern-readable-code-beats-100-runtime-eqc0

// #include <ranges>
// #include <string>
// #include <vector>

class Solution {
public:
// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    std::vector<std::string> divideString(
        std::string const & str_,
        int const groupSz_,
        char const chrFill_
    ) const;
};

std::vector<std::string> Solution::divideString(
    std::string const & str_,
    int const groupSz_,
    char const chrFill_
) const {
    namespace views = std::views;
    auto const strSz{str_.size()};
    auto groups{std::vector<std::string>{}};
    auto const groupsCount{(strSz / groupSz_) + 1};
    groups.reserve(groupsCount);
    for(auto const idxBegin: views::iota(0u, strSz) | views::stride(groupSz_)
    ) {
        groups.emplace_back(str_.substr(idxBegin, groupSz_));    
    }
    auto const fillSz{groupSz_ - groups.back().size()}; 
    groups.back().append(fillSz, chrFill_);
    return groups;
}
