// problem : https://leetcode.com/problems/adjacent-increasing-subarrays-detection-i/description
// submission : https://leetcode.com/problems/adjacent-increasing-subarrays-detection-i/submissions/1801786659
// solution post : https://leetcode.com/problems/adjacent-increasing-subarrays-detection-i/solutions/7275830/
//    c-modern-readable-code-optimal-time-comp-w2uz

// import std;

class Solution {
public:
// let 'n' be the number of the given numbers
// time complexity O(n)
// space complexity O(1)
// runtime 8 ms, beats 89.09 %
    [[nodiscard]]
    auto hasIncreasingSubarrays(
        std::vector<int> const & nums_,
        int subArrSz_
    ) const -> bool;

private:
    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
};

auto Solution::hasIncreasingSubarrays(
    std::vector<int> const & nums_,
    int subArrSz_
) const -> bool {
    namespace rngs = std::ranges;

    auto prevSubArrSz{0};
    auto currSubArrSz{1};
    auto maxSubArrSz{0};
    for(auto prevNum{nums_.cbegin()}, currNum{nums_.cbegin() + 1},
            numEnd{nums_.cend()};
        currNum != numEnd;
        ++prevNum, ++currNum
    ) {
        if(*prevNum < *currNum) {
            ++currSubArrSz;
        } else {
            prevSubArrSz = currSubArrSz;
            currSubArrSz = 1;
        }
        maxSubArrSz = rngs::max({
            maxSubArrSz,
            std::min(prevSubArrSz, currSubArrSz),
            currSubArrSz / 2
        });
        if(maxSubArrSz >= subArrSz_) {
            return true;
        }
    }
    return false;
}
