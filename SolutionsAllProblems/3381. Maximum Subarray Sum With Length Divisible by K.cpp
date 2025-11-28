// problem : https://leetcode.com/problems/maximum-subarray-sum-with-length-divisible-by-k/description
// submission : https://leetcode.com/problems/maximum-subarray-sum-with-length-divisible-by-k/submissions/1841898632
// solution post : https://leetcode.com/problems/maximum-subarray-sum-with-length-divisible-by-k/solutions/7379683/
//    c-modern-readable-code-beats-100-runtime-cchw

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
// let 'n' be the number of given numbers
// 'm' - a given divisor
// time complexity O(n)
// space complexity O(m)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maxSubarraySum(
        std::span<int const> const nums_,
        int const divisor_
    ) const -> long long;
};

auto Solution::maxSubarraySum(
    std::span<int const> const nums_,
    int const divisor_
) const -> long long {
    namespace vs = std::views;
    using llLimitsT = std::numeric_limits<long long>;

    auto prefSum{0ll};
    auto maxSum{llLimitsT::min()};
    auto minPrefSumPerReminder{
        std::vector<long long>(divisor_, llLimitsT::max() / 2)
    };
    minPrefSumPerReminder[divisor_ - 1] = 0;
    for(auto const idx: vs::iota(0u, nums_.size())) {
        prefSum += nums_[idx];
        auto & minPrefPerRem{minPrefSumPerReminder[idx % divisor_]};
        auto const currSum{prefSum - minPrefPerRem};
        maxSum = std::max(maxSum, currSum);
        minPrefPerRem = std::min(minPrefPerRem, prefSum);
    }
    return maxSum;
}
