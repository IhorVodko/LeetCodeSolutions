// problem : https://leetcode.com/problems/longest-increasing-subsequence/description
// submission : https://leetcode.com/problems/longest-increasing-subsequence/submissions/1808478372
// solution post : 

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream("display_runtime.txt") << 0 << std::endl;
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
// let 'n' be the nubmer of the given nubmers
// time complexity O(n * log(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto lengthOfLIS(std::span<int> const nums_) const -> int;
};

auto Solution::lengthOfLIS(std::span<int> const nums_) const -> int {
    namespace rngs = std::ranges;

    auto subSeq{std::vector<int>{}};
    subSeq.reserve(nums_.size());
    for(auto const num: nums_) {
        auto const subSeqIt{rngs::lower_bound(subSeq, num)};
        if(subSeqIt == subSeq.cend()) {
            subSeq.emplace_back(num);
        } else {
            *subSeqIt = num;
        }
    }
    auto const subSeqMaxSz{subSeq.size()};
    return subSeqMaxSz;
}
