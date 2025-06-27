// problem : https://leetcode.com/problems/longest-subsequence-repeated-k-times/description/
// submission : https://leetcode.com/problems/longest-subsequence-repeated-k-times/submissions/1678445355
// solution post : https://leetcode.com/problems/longest-subsequence-repeated-k-times/solutions/6892728/
//    c-modern-readable-code-optimal-time-comp-2t4f

// #include <queue>
// #include <ranges>
// #include <string>
// #include <vector>

namespace Util {
    inline auto constexpr kChrSetSz{26};
    inline auto constexpr kChrSetBegin{'a'};
}

class Solution {
public:
// let 'n' be a length of the given string
// let 'r' be a required count of the greatest subqequence repetitions
// time complexity O(n * floor(n / k)!)
// space complexity O(floor(n / k)!)
// runtime 114 ms, beats 92.75 %
    std::string longestSubsequenceRepeatedK(
        std::string_view const str_,
        int const subeqRepetionsCount_
    );
private:
    [[nodiscard]]
    bool IsKRepeatedSubseq(
        std::string_view const subeq_, 
        int const subeqRepetionsCount_
    ) const;
    [[nodiscard]]
    static constexpr int ChrToNum(char const chr_);
    [[nodiscard]]
    static constexpr int NumToChr(int const num_);
    std::string_view mStr;
};

std::string Solution::longestSubsequenceRepeatedK(
    std::string_view const str_,
    int const subeqRepetionsCount_
) {
    using namespace Util;
    namespace views = std::views;
    mStr = str_;
    auto chrCounts{std::array<int, kChrSetSz>{}};
    for(auto const chr: mStr) {
        ++chrCounts.at(ChrToNum(chr));
    }
    auto chrCandidates{std::vector<char>{}};
    chrCandidates.reserve(kChrSetSz);
    for(auto const idx: views::iota(0, kChrSetSz) | views::reverse) {
        if(chrCounts.at(idx) >= subeqRepetionsCount_) {
            chrCandidates.emplace_back(NumToChr(idx));
        }
    }
    auto subseqsQ{std::queue<std::string>{}};
    for(auto const chr: chrCandidates) {
        subseqsQ.emplace(std::string{chr});
    }
    auto subseqMax{std::string{}};
    while(!subseqsQ.empty()) {
        auto const subseqCurr{subseqsQ.front()};
        subseqsQ.pop();
        if(subseqCurr.size() > subseqMax.size()) {
            subseqMax = subseqCurr;
        }
        for(auto const chr: chrCandidates) {
            auto subseqNext{subseqCurr + chr};
            if(IsKRepeatedSubseq(subseqNext, subeqRepetionsCount_)) {
                subseqsQ.emplace(std::move(subseqNext));
            }
        }
    }
    return subseqMax;
}

bool Solution::IsKRepeatedSubseq(
    std::string_view const subeq_,
    int const subeqRepetionsCount_
) const {
    auto idx{0};
    auto matchedSubseqsCount{0};
    auto const subsqSz{subeq_.size()};
    for(auto const chr: mStr) {
        if(chr == subeq_.at(idx) && ++idx == subsqSz) {
            idx = 0;
            if(++matchedSubseqsCount == subeqRepetionsCount_) {
                return true;        
            }
        }
    }
    return false;
}

constexpr int Solution::ChrToNum(char const chr_) {
    using namespace Util;
    auto num{chr_ - kChrSetBegin};
    return num;
}

constexpr int Solution::NumToChr(int const num_) {
    using namespace Util;
    auto chr{kChrSetBegin + num_};
    return chr;
}
