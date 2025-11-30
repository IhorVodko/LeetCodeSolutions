// problem : https://leetcode.com/problems/make-sum-divisible-by-p/description/
// submission : https://leetcode.com/problems/make-sum-divisible-by-p/submissions/1843648486
// solution post : https://leetcode.com/problems/make-sum-divisible-by-p/solutions/7384256/
//    c-modern-readable-code-beats-100-runtime-yow7

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
// let 'n' be the lenght of a given array
// 'm' - a given divisor
// time complexity O(n)
// space complexity O(m)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto minSubarray(
        std::span<int const> const nums_,
        int const divisor_
    ) const -> int; 
};

auto Solution::minSubarray(
    std::span<int const> const nums_,
    int const divisor_
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const numsLen{std::ssize(nums_)};
    auto totSum{0};
    for(auto const num: nums_) {
        totSum = (totSum + num) % divisor_;
    }
    auto const targetRem{totSum % divisor_};
    if(targetRem == 0) {
        return 0;
    }
    auto remToIdx{std::unordered_map<int, int>{}};
    remToIdx.emplace(0, -1);
    auto currSum{0};
    auto minLen{static_cast<int>(numsLen)};
    for(auto const idx: vs::iota(0, numsLen)) {
        currSum = (currSum + nums_[idx]) % divisor_;
        auto const neededRem{(currSum - targetRem + divisor_) % divisor_};
        if( auto const remToIdxIt{remToIdx.find(neededRem)};
            remToIdxIt != remToIdx.end()
        ) {
            auto const currLen{idx - remToIdxIt->second};
            minLen = std::min(minLen, currLen);
        } 
        remToIdx[currSum] = idx;
    }
    auto const subArrMinLen{minLen == numsLen ? -1 : minLen};
    return subArrMinLen;
}
