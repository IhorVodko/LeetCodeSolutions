// problem : https://leetcode.com/problems/valid-triangle-number/description
// submission : https://leetcode.com/problems/valid-triangle-number/submissions/1783213745
// solution post : https://leetcode.com/problems/valid-triangle-number/solutions/7225427/
//    c-modern-readable-code-optimal-time-comp-k3qo

// import std;

class Solution {
public:
// let 'n' be the count of the given numbers
// time complexity O(n^2)
// space complexity O(1)
// runtime 51 ms, beats 28.03 %
    [[nodiscard]]
    auto triangleNumber(std::vector<int> & nums_) const -> int;

private:
    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
};

auto Solution::triangleNumber(std::vector<int> & nums_) const -> int {
    namespace ranges = std::ranges;
    namespace views = std::views;
    auto const numsSz{std::ssize(nums_)};
    if(numsSz < 3) {
        return 0;
    }
    auto tripletsCnt{0};
    ranges::sort(nums_);
    for(auto const idxLargestSide: views::iota(2, numsSz) | views::reverse) {
        auto idxSide1{0};
        auto idxSide2{idxLargestSide - 1};
        auto const largestSize{nums_.at(idxLargestSide)};
        while(idxSide1 < idxSide2) {
            if( auto const sum2Sides{nums_.at(idxSide1) + nums_.at(idxSide2)};
                sum2Sides > largestSize
            ) {
                auto const currTripletsCnt{idxSide2 - idxSide1};
                tripletsCnt += currTripletsCnt;
                --idxSide2;
            } else {
                ++idxSide1;
            }
        }
    }
    return tripletsCnt;
}
