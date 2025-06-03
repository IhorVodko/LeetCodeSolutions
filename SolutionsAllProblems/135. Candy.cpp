// problem : https://leetcode.com/problems/candy/description
// submission : https://leetcode.com/problems/candy/submissions/1652930077
// solution post : https://leetcode.com/problems/candy/solutions/6808332/
//    c-modern-readable-code-beats-100-runtime-mb5a

// #include <algorithm>
// #include <vector>

class Solution {
public:
// let 'n' be a count of rankings given 
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    int candy(std::vector<int> const & rankings_) const;
private:
    int Count(int const num_) const;
};

int Solution::candy(std::vector<int> const & rankings_) const {
    auto const rankingCount{rankings_.size()};
    if(rankingCount <= 1) {
        return rankingCount;
    }
    auto candyCount{0};
    auto upRatingShiftCount{0};
    auto downRatingShiftCount{0};
    auto slopePrev{0};
    auto slopeCurr{0};
    for(auto i{1}; i < rankingCount; ++i) {
        slopePrev = slopeCurr;
        if(rankings_.at(i) > rankings_.at(i - 1)) {
            slopeCurr = 1;
        } else {
            slopeCurr = rankings_.at(i) < rankings_.at(i - 1) ? -1 : 0;
        }
        if((slopePrev > 0 && slopeCurr == 0) ||
            (slopePrev < 0 && slopeCurr >= 0) 
        ) {
            candyCount += Count(upRatingShiftCount) +
                Count(downRatingShiftCount) +
                std::max(upRatingShiftCount, downRatingShiftCount);
            upRatingShiftCount = 0;
            downRatingShiftCount = 0;
        }
        if(slopeCurr > 0) {
            ++upRatingShiftCount;
        } else if(slopeCurr < 0) {
            ++downRatingShiftCount;
        } else {
            ++candyCount;
        }
    }
    candyCount += Count(upRatingShiftCount) + Count(downRatingShiftCount) +
        std::max(upRatingShiftCount, downRatingShiftCount) + 1;
    return candyCount;
}

int Solution::Count(int const num_) const {
    auto const sum{num_ * (num_ + 1) / 2};
    return sum; 
}
