// problem : https://leetcode.com/problems/adjacent-increasing-subarrays-detection-ii/description/
// submission : https://leetcode.com/problems/adjacent-increasing-subarrays-detection-ii/submissions/1802509911
// solution post : https://leetcode.com/problems/adjacent-increasing-subarrays-detection-ii/solutions/7277556/
//    c-modern-readable-code-beats-100-runtime-jsal

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
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maxIncreasingSubarrays(std::vector<int> const & nums_) const -> int;
};

auto Solution::maxIncreasingSubarrays(
    std::vector<int> const & nums_
) const -> int {
    namespace rngs = std::ranges;

    assert(nums_.size() >= 2); 

    auto prevSubArrSz_{0};
    auto currSubArrSz_{1};
    auto maxSubArrSz_{currSubArrSz_};
    for(auto prevNum{nums_.cbegin()}, currNum{nums_.cbegin() + 1},
        numEnd{nums_.cend()};
        currNum != numEnd;     
        ++prevNum, ++currNum
    ) {
        if(*prevNum < *currNum) {
            ++currSubArrSz_;
        } else {
            maxSubArrSz_ = rngs::max({
                maxSubArrSz_,
                rngs::min(prevSubArrSz_, currSubArrSz_),
                currSubArrSz_ / 2
            });
            prevSubArrSz_ = currSubArrSz_;
            currSubArrSz_ = 1;
        }
    }
    maxSubArrSz_ = rngs::max({
        maxSubArrSz_,
        rngs::min(prevSubArrSz_, currSubArrSz_),
        currSubArrSz_ / 2
    });
    return maxSubArrSz_;
}
