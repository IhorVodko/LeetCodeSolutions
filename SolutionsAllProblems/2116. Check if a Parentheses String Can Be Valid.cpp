// problem : https://leetcode.com/problems/check-if-a-parentheses-string-can-be-valid/description/
// submission : https://leetcode.com/problems/check-if-a-parentheses-string-can-be-valid/submissions/1506649549
// solution post : https://leetcode.com/problems/check-if-a-parentheses-string-can-be-valid/solutions/6271016/c-modern-readable-code-optimal-time-comp-siyh

// #include <string>

namespace Utility {
    auto constexpr unlocked{'0'};
    auto constexpr locked{'1'};
    auto constexpr open{'('};
    auto constexpr closed{')'};
}

// let 'n' be a parameter 'str' length
// time complexity O(n)
// space complexity O(1)
// runtime 12 ms, beats 68.59 %
class Solution {
public:
    bool canBeValid(
        std::string const & str,
        std::string const & lockedMask
    ) {
        using namespace Utility;
        Reset();
        if(str.size() %2 == 1) {
            return false;
        }
        if(IsClosedBracketsMathced(str, lockedMask) && 
            IsOpenBracketsMathced(str, lockedMask)
        ) {
            return true;
        }
        return false;
    }
    Solution():
        openUnmathcedCount{0},
        unlockedCount{0}
    {}
private:
    void Reset() {
        openUnmathcedCount = 0;
        unlockedCount = 0;
    }
    bool IsClosedBracketsMathced(
        std::string const & str,
        std::string const & lockedMask
    ) {
        using namespace Utility;
        for(auto i{0}; i < str.size(); ++i) {
            if(lockedMask.at(i) == unlocked) {
                ++unlockedCount;
                continue;
            }
            if(str.at(i) == open) {
                ++openUnmathcedCount;
            } else {
                if(openUnmathcedCount) {
                    --openUnmathcedCount;
                } else if(unlockedCount) {
                    --unlockedCount;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
    bool IsOpenBracketsMathced(
        std::string const & str,
        std::string const & lockedMask
    ) {
        using namespace Utility;
        auto balancedCount{0};
        for(auto i{str.size() - 1}; i + 1 >= 1; --i) {
            if(lockedMask.at(i) == unlocked) {
                --balancedCount;
                --unlockedCount;
                continue;
            }
            if(str.at(i) == open) {
                    ++balancedCount;
                    --openUnmathcedCount;
            } else {
                --balancedCount;
            }
            if(balancedCount > 0) {
                return false;
            }
            if(!unlockedCount && !openUnmathcedCount) {
                return true;
            }
        };
        return openUnmathcedCount <= 0;
    }
    int openUnmathcedCount;
    int unlockedCount;
};
