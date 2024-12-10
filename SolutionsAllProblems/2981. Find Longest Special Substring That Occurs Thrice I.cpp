// problem : https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-i/description/
// submission : https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-i/submissions/1475331527
// solution post : https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-i/solutions/6133067/c-modern-readable-code-beats-100-runtime 


// #include <array>
// #include <algorithm>
// #include <string>
// #include <unordered_map>


class Solution {
public:
    // let 'n' be an input length
    // time complexity O(n)
    // space complexity O(n)
    // runtime 0 ms, beats 100.00 %
    int maximumLength(
        std::string const str
    ) const {
        return FindLongestSpecialSubStr(str, CountSpecialSubstrings(str));
    }
private:
    size_t static constexpr maxStrLength{50};
    using mapT = std::unordered_map<char, std::array<size_t, maxStrLength>>;
    mapT CountSpecialSubstrings(
        std::string const &
    ) const;
    int FindLongestSpecialSubStr(
        std::string const &,
        mapT const
    ) const;
    size_t static constexpr defautlVal{0};
    size_t static constexpr minRequeiredFrequency{3};
    char static constexpr defautlChar{'a'};
};

Solution::mapT Solution::CountSpecialSubstrings(
    std::string const & str
) const {
    auto subStrsCount{mapT{}};
    auto frequencyTemp{size_t{defautlVal}};
    auto chrTemp{defautlChar};
    for(auto chr{str.cbegin()}, end{str.cend()}; chr < end;) {
        chrTemp = *chr;
        frequencyTemp = defautlVal;
        if(!subStrsCount.contains(chrTemp)) {
            subStrsCount.emplace(chrTemp, mapT::mapped_type{});
        }
        auto & frequencies = subStrsCount[chrTemp];
        while(chr < end && *chr == chrTemp) {
            ++frequencyTemp;
            for_each(frequencies.begin(), frequencies.begin() +
                frequencyTemp, [&] (auto & frequency) {
                    ++frequency;
            });
            ++chr;
        }
    }
    return subStrsCount;
}

int Solution::FindLongestSpecialSubStr(
        std::string const & str,
        mapT const subStrsCount
) const {
    auto maxLength{long{1}};
    for(auto const & [chr, frequencies]: subStrsCount) {
        for(auto length{frequencies.rbegin()}, end{frequencies.rend()};
            length < end; ++length
        ) {
            if(*length < minRequeiredFrequency) {
                continue;
            }
            maxLength = std::min(maxLength, std::distance(
                frequencies.rend(), length));
            break;
        }
    }
    return -1 * maxLength;
}
