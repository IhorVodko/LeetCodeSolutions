// problem : https://leetcode.com/problems/count-elements-with-maximum-frequency/description
// submission : https://leetcode.com/problems/count-elements-with-maximum-frequency/submissions/1778949813
// solution post : https://leetcode.com/problems/count-elements-with-maximum-frequency/solutions/7213444/
//    c-modern-readable-code-beats-100-runtime-rccl

// import std;

class Solution {
public:
// let 'n' be a given nums' count
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maxFrequencyElements(std::vector<int> const & nums_) const -> int;

private:
    inline static int constexpr kMaxNumCnt{101};
};

auto Solution::maxFrequencyElements(
    std::vector<int> const & nums_
) const -> int {
    namespace ranges = std::ranges;
    namespace views = std::views;
    
    auto maxFreq{-1};
    auto maxFreqSum{0};
    auto freqs{std::array<int, kMaxNumCnt>{}};
    for(auto const num: nums_) {
        auto const freq{++freqs.at(num)};
        if(freq == maxFreq) {
            maxFreqSum += freq;
        } else if(freq > maxFreq) {
            maxFreq = freq;
            maxFreqSum = freq;
        }
    }
    return maxFreqSum;
}
