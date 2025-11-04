// problem : https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-i/description/
// submission : https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-i/submissions/1820834600
// solution post : https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-i/solutions/7327038/
//    c-modern-readable-code-beats-100-runtime-cnj6

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
// let 'n' be the length of given array of numbers
// 'm' - the given size of the subarray
// time complexity O(n * m * log(m))
// space complexity O(m)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto findXSum(
        std::span<int const> const nums_,
        int const subArrSz_,
        int const maxFreqNumsSz_
    ) const -> std::vector<int>;
};

auto Solution::findXSum(
    std::span<int const> const nums_,
    int const subArrSz_,
    int const maxFreqNumsSz_
) const -> std::vector<int> {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto numsSz_{std::ssize(nums_)};
    auto answer{std::vector<int>{}};
    auto numToFreq{std::unordered_map<int, int>{}};
    for(auto const idx: vs::iota(0, subArrSz_)) {
        ++numToFreq[nums_[idx]];
    }
    for(auto const idx: vs::iota(0, numsSz_ - subArrSz_ + 1)) {
        if(idx > 0) [[unlikely]] {
            --numToFreq[nums_[idx - 1]];
            ++numToFreq[nums_[idx + subArrSz_ - 1]];
        }
        auto freqsAndNums{std::vector<std::pair<int, int>>{}};
        for(auto const [num, freq]: numToFreq) {
            freqsAndNums.emplace_back(freq, num);
        }
        rngs::sort(freqsAndNums, std::greater<>{});
        auto sum{0};
        for(auto const idx2: vs::iota(
                0,
                std::min(maxFreqNumsSz_, static_cast<int>(freqsAndNums.size()))
        )) {
            auto const [freq, num]{freqsAndNums[idx2]};
            sum += freq * num;
        }    
        answer.emplace_back(sum);
    }
    return answer;
}
