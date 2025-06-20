// problem : https://leetcode.com/problems/maximum-manhattan-distance-after-k-changes/description
// submission : https://leetcode.com/problems/maximum-manhattan-distance-after-k-changes/submissions/1670607669
// solution post : https://leetcode.com/problems/maximum-manhattan-distance-after-k-changes/solutions/6865936/
//    c-modern-readable-code-optimal-time-comp-aawa

// #include <algorithm>
// #include <rangese>
// #include <stdexcept>
// #include <vector>

namespace Util {
    inline auto constexpr kNorth{'N'};
    inline auto constexpr kSouth{'S'};
    inline auto constexpr kWest{'W'};
    inline auto constexpr kEast{'E'};
}

class Solution {
public:
// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(1)
// runtime 45 ms, beats 93.64 %
    [[nodiscard]]
    int maxDistance(
        std::string const & movements_,
        int const changeCountAllowed_
    ) const;
};

int Solution::maxDistance(
    std::string const & movements_,
    int const changeCountAllowed_
) const {
    using namespace Util;
    auto deltaVertical{0};
    auto deltaHorizontal{0};
    auto movementsSz{movements_.size()};
    auto distanceMax{0};
    for(auto const idx: std::ranges::iota_view{0, static_cast<int>(movementsSz)}
    ) {
        switch(movements_.at(idx)) {
            case kNorth: {
                ++deltaVertical;
                break;
            }
            case kSouth: {
                --deltaVertical;
                break;
            }
            case kWest: {
                ++deltaHorizontal;
                break;
            }
            case kEast: {
                --deltaHorizontal;
                break;
            }
            default: {
                throw std::invalid_argument("oops!");
                break;
            } 
        }
        auto const distanceIfAllChanges{std::abs(deltaVertical) +
            std::abs(deltaHorizontal) + changeCountAllowed_ * 2};
        auto const distanceMaxIfNoChanges{idx + 1}; 
        distanceMax = std::max(distanceMax,
            std::min(distanceIfAllChanges, distanceMaxIfNoChanges));
    }
    return distanceMax;
}
