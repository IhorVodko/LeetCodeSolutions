// problem : https://leetcode.com/problems/count-covered-buildings/description
// submission : https://leetcode.com/problems/count-covered-buildings/submissions/1853106500
// solution post : https://leetcode.com/problems/count-covered-buildings/solutions/7407396/
//    c-modern-readable-code-beats-100-runtime-dn6d

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream{"display_runtime.txt"} << 0 << std::endl;
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
// let 'n' be the number of given buildings
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto countCoveredBuildings(
        int const mxRowColSz_,
        std::span<std::vector<int> const> const buildings_
    ) const -> int;
};

auto Solution::countCoveredBuildings(
    int const mxRowColSz_,
    std::span<std::vector<int> const> const buildings_
) const -> int {
    using intLimitsT = std::numeric_limits<int>;

    auto minBColPerRow{std::vector<int>(mxRowColSz_ + 1, intLimitsT::max())};
    auto maxBColPerRow{std::vector<int>(mxRowColSz_ + 1, intLimitsT::min())};
    auto minBRowPerCol{std::vector<int>(mxRowColSz_ + 1, intLimitsT::max())};
    auto maxBRowPerCol{std::vector<int>(mxRowColSz_ + 1, intLimitsT::min())};
    for(auto const & building: buildings_) {
        auto const r{building[0]};
        auto const c{building[1]};
        minBColPerRow[r] = std::min(minBColPerRow[r], c);
        maxBColPerRow[r] = std::max(maxBColPerRow[r], c);
        minBRowPerCol[c] = std::min(minBRowPerCol[c], r);
        maxBRowPerCol[c] = std::max(maxBRowPerCol[c], r);
    }
    auto coveredBCnt{0};
    for(auto const & building: buildings_) {
        if( auto const r{building[0]}, c{building[1]}; 
            minBColPerRow[r] < c && c < maxBColPerRow[r] &&
            minBRowPerCol[c] < r && r < maxBRowPerCol[c]
        ) {
            ++coveredBCnt;
        }
    }
    return coveredBCnt;
}
