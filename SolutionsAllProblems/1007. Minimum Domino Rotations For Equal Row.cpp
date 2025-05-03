// problem : https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/description/
// submission : https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/submissions/1624498628
// solution post : https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/solutions/6711191/
//     c-modern-readable-code-beats-100-runtime-p72d

// #include <algorithm>
// #include <vector>

class Solution {
public:
// let 'n' be a count of the given dominoes
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    int minDominoRotations(
        std::vector<int> & topVals_,
        std::vector<int> & bottomVals_
    ) const;
private:
    int CountMinRotations(
        int const val_,
        std::vector<int> const & vals1_,
        std::vector<int> const & vals2_
    ) const;
};

int Solution::minDominoRotations(
    std::vector<int> & topVals_,
    std::vector<int> & bottomVals_
) const {
    auto const rotationsCount{
        CountMinRotations(topVals_.at(0), topVals_, bottomVals_)};
    if(rotationsCount != -1 || topVals_.at(0) == bottomVals_.at(0)) {
        return rotationsCount;
    }
    return CountMinRotations(bottomVals_.at(0), topVals_, bottomVals_);
}

int Solution::CountMinRotations(
    int const val_,
    std::vector<int> const & vals1_,
    std::vector<int> const & vals2_
) const {
    auto rotationsCount1{0};
    auto rotationsCount2{0};
    auto const valsCount{vals1_.size()};
    for(auto i{0}; i < valsCount; ++i) {
        if(!(vals1_[i] == val_ || vals2_[i] == val_)) {
            return -1;
        } else if(vals1_[i] != val_) {
            ++rotationsCount1;
        } else if(vals2_[i] != val_){
           ++rotationsCount2; 
        }
    }
    return std::min(rotationsCount1, rotationsCount2); 
}
