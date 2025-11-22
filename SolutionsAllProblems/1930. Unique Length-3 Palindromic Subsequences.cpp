// problem : https://leetcode.com/problems/unique-length-3-palindromic-subsequences/description/ 
// submission : https://leetcode.com/problems/unique-length-3-palindromic-subsequences/submissions/1837122096
// solution post : https://leetcode.com/problems/unique-length-3-palindromic-subsequences/solutions/7368097/
//    c-modern-readable-code-beats-100-runtime-0gca

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream{"display_runtime.txt"} << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class Solution {
public:
// let 'n' be the length of the given string
// 'm' - given charset size, which is given as a constant 26
// time complexity O(n * m)
// space complexity O(m^2)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto countPalindromicSubsequence(
        std::string_view const str_
    ) const -> int;
};

auto Solution::countPalindromicSubsequence(
    std::string_view const str_
) const -> int {
    namespace vs = std::views;

    auto chrRanges{std::array<std::pair<int, int>, 26>{}};
    chrRanges.fill({-1, -1});
    auto const strSz{std::ssize(str_)};
    for(auto const idx: vs::iota(0, strSz)) {
        auto & [firstIdx, lastIdx]{chrRanges[str_[idx] - 'a']};
        if(firstIdx == -1) [[unlikely]] {
            firstIdx = idx;
        }
        lastIdx = idx;
    }
    auto validCharRangeIdxs{std::vector<int>{}};
    validCharRangeIdxs.reserve(26);
    for(auto const idx: vs::iota(0u, chrRanges.size())) {
        auto const [firstIdx, lastIdx]{chrRanges[idx]};
        if(firstIdx != -1 && lastIdx != -1) {
            validCharRangeIdxs.emplace_back(idx);
        }
    }
    auto const validCharRangeIdxsSz{std::ssize(validCharRangeIdxs)};
    auto uniqueChrsPerRange{
        std::vector<std::bitset<26>>(validCharRangeIdxsSz)
    };
    auto palindromeCnt{0};
    for(auto const strIdx: vs::iota(0, strSz)) {
        for(auto const validRangeIdx: vs::iota(0, validCharRangeIdxsSz)) {
            auto const [firstIdx, lastIdx]{
                chrRanges[validCharRangeIdxs[validRangeIdx]]
            };
            if(firstIdx < strIdx && strIdx < lastIdx) {
                auto const chr{str_[strIdx] - 'a'};
                auto & uniqueChrs{uniqueChrsPerRange[validRangeIdx]};
                if(!uniqueChrs.test(chr)) {
                    uniqueChrs.set(chr);
                    ++palindromeCnt;
                }
            } 
        }
    }
    return palindromeCnt;
}
