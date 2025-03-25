// problem : https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/description/
// submission : https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/submissions/1585680649
// solution post : https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/solutions/6578322/
//     c-modern-readable-code-optimal-time-comp-kqwv

// #include <algorithm>
// #include <vector>

namespace Utility{
    enum class Dimensions {
        X,
        Y
    };
}

// let 'n' be a count of rectangles given
// time complexity O(n * log2(n));
// space complexity O(std::sort(args))
// runtime 140 ms, beats 67.62 %
class Solution {
public:
    using Arr2T = std::vector<std::vector<int>>;
    bool checkValidCuts(
        int const gridSize_,
        Arr2T & rectangles_
    ) const {
        using namespace Utility;
        return doesCutsExist(rectangles_, Dimensions::X) ||
            doesCutsExist(rectangles_, Dimensions::Y);
    }
private:
    bool doesCutsExist(
        Arr2T & rectangles_,
        Utility::Dimensions const dim_  
    ) const {
        using namespace Utility;
        auto const dimPosition{dim_ == Dimensions::X ? 0 : 1};
        std::sort(rectangles_.begin(), rectangles_.end(), [=](
            auto const & _lhs,
            auto const & _rhs
        ) {
            return _lhs.at(dimPosition) < _rhs.at(dimPosition);
        });
        auto const endCoordinate{dimPosition + 2};
        auto furthestEnd{rectangles_.at(0).at(endCoordinate)};
        auto gapsCount{0};
        for(auto i{1}; i < rectangles_.size(); ++i) {
            auto & rectangle{rectangles_.at(i)};
            if(furthestEnd <= rectangle.at(dimPosition)) {
                if(++gapsCount == 2) {
                    return true;        
                }
            }
            furthestEnd = std::max(furthestEnd, rectangle.at(endCoordinate));
        }
        return false;
    }
};
