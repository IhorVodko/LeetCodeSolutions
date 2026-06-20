// problem : https://leetcode.com/problems/maximum-building-height/description
// submission : https://leetcode.com/problems/maximum-building-height/submissions/2040211205
// solution post : https://leetcode.com/problems/maximum-building-height/solutions/8347852/c-modern-readable-code-optimal-time-comp-sbb4

// Approach : Multi-Pass Constraint Propagation
// Runtime : 31 ms, beats 97.2 %


// Complexity
// let 'n' be the number of restrictions
// Time :  O(n * log(n))
// Space : O(n)

// import std;

#define NDEBUG

#include <cassert>

class Solution final {
public:
    [[nodiscard]]
    static auto maxBuilding(
        int const buildingsTot_,
        std::vector<std::vector<int>> const & idAndUpLimHeightArr_
    ) -> int;
};

auto Solution::maxBuilding(
    int const buildingsTot_,
    std::vector<std::vector<int>> const & idAndUpLimHeightArr_
) -> int {
    namespace rs = std::ranges;
    namespace vs = std::views;

    // precondition ======================================================================
    assert(2 <= buildingsTot_ && buildingsTot_ <= 1'000'000'000);
    assert(0 <= idAndUpLimHeightArr_.size() &&
        idAndUpLimHeightArr_.size() <= std::min(buildingsTot_ - 1, 100'000)
    );
    assert(rs::all_of(idAndUpLimHeightArr_, [=] (auto const idAndUpLimHeight_) {
        auto const id{idAndUpLimHeight_[0]};
        auto const upLim{idAndUpLimHeight_[1]};
        return 2 <= id && id <= buildingsTot_ &&
            0 <= upLim && upLim <= 1'000'000'000;
    }));
    assert([&] () {
        auto ids{std::unordered_set<int>{}};
        for(auto const & idAndUpLimHeight: idAndUpLimHeightArr_) {
            if(!ids.emplace(idAndUpLimHeight[0]).second) {
                return false;
            }
        }
        return true;
    }());
   // ====================================================================================

    auto idAndUpLimHArr{
        idAndUpLimHeightArr_ |
        vs::transform([] (auto const & idAndUpLimH_) {
            return std::pair{idAndUpLimH_[0], idAndUpLimH_[1]};
        }) |
        rs::to<std::vector>()
    };

    // Enforce implicit endpoints
    idAndUpLimHArr.emplace_back(1, 0);
    idAndUpLimHArr.emplace_back(buildingsTot_, buildingsTot_ - 1);

    rs::sort(idAndUpLimHArr);

    // Propagate height limits rightward
    for(auto [currIdAndUpLimH, nextIdAndUpLimH]: idAndUpLimHArr | vs::pairwise) {
        auto const [currId, currH]{currIdAndUpLimH};
        auto & [nextId, nextH]{nextIdAndUpLimH};
        nextH = std::min(nextH, currH + nextId - currId);
    } 

    // Propagate height limits leftward
    for(auto [currIdAndUpLimH, nextIdAndUpLimH] :
            idAndUpLimHArr | vs::reverse | vs::pairwise
    ) {
        auto const [currId, currH]{currIdAndUpLimH};
        auto & [nextId, nextH]{nextIdAndUpLimH};
        nextH = std::min(nextH, currH + currId - nextId);
    }

    // Find highest peak between bounds
    auto const CompMaxHs{[] (auto const currAndNextIdAndUpLimH_) {
        auto const [currIdAndUpLimH, nextIdAndUpLimH]{currAndNextIdAndUpLimH_};
        auto const [currId, currH]{currIdAndUpLimH};
        auto const [nextId, nextH]{nextIdAndUpLimH};
        // Formula mathematically prevents 32-bit signed integer overflow
        auto const maxH{currH + (nextH - currH + nextId - currId) / 2};

        return maxH;
    }};

    auto maxHs{idAndUpLimHArr | vs::pairwise | vs::transform(CompMaxHs)};
    auto const maxH{rs::max(maxHs)};

    // postcondition =====================================================================
    assert(maxH >= 0);
    // ===================================================================================

    return maxH;
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
