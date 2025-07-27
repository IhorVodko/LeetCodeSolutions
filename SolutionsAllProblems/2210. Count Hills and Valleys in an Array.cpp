// problem : https://leetcode.com/problems/count-hills-and-valleys-in-an-array/description
// submission : https://leetcode.com/problems/count-hills-and-valleys-in-an-array/submissions/1713751902
// solution post : https://leetcode.com/problems/count-hills-and-valleys-in-an-array/solutions/7013111
//    /c-modern-readable-code-beats-100-runtime-93kc

// #include <vector>

class Solution {
public:
// let 'n' be a count of the given numbers
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    int countHillValley(std::vector<int> const & nums_) const;
private:
    [[nodiscard]]
    bool IsHillOrValley(
        int const prevNum_,
        int const currNum_,
        int const nextNum_
    ) const;
};

int Solution::countHillValley(std::vector<int> const & nums_) const {
    auto hvCounter{0};
    auto const numsEnd{nums_.size()};
    for(auto currNum{nums_.begin() + 1},  lastNum{nums_.end() - 1},
            numsEnd{nums_.end()};
        currNum < lastNum;
    ) {
        auto prevNum{currNum - 1};
        auto nextNum{currNum + 1};
        while(nextNum < numsEnd && *currNum == *nextNum) {
            ++nextNum;    
        } 
        if(nextNum == numsEnd) {
            return hvCounter;
        }
        if(IsHillOrValley(*prevNum, *currNum, *nextNum)) {
            ++hvCounter;
        }
        currNum = nextNum;
    }
    return hvCounter;
}

bool Solution::IsHillOrValley(
    int const prevNum_,
    int const currNum_,
    int const nextNum_
) const {
    auto const isHillOrVallye( 
        (currNum_ < prevNum_ && currNum_ < nextNum_) ||
        (currNum_ > prevNum_ && currNum_ > nextNum_)
    );
    return isHillOrVallye;     
}
