// problem : https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/description
// submission : https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/submissions/2157403883
// solution post : https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/solutions/8547310/
//    simplanation-simple-explanation-by-cyber-9e08

// Approach : Dynamic Programming with Bitsets
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' by 'm' be the given greed size
// Time :  O(n * m)
// Space : O(m)

// import std;

// #include <bitset>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <tuple>
// #include <vector>

// #include <cstddef>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

constexpr auto kMaxBalanceCnt   {100uz};
constexpr auto kBalanceDelta    {1uz};
constexpr auto kInitBalance     {1uz};
constexpr auto kValidBalanceIdx {0uz};
constexpr auto kOpenBracket     {'('};
constexpr auto kCloseBracket    {')'};
constexpr auto kPathNotFound    {false};

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

using std::size_t;
using dpBalanceRec = std::bitset<kMaxBalanceCnt>;

constexpr auto isOdd{[] [[nodiscard]] (size_t const num_) static -> bool {
    return num_ % 2uz == 1uz;
}};

constexpr auto isPositive{[] [[nodiscard]] (size_t const num_) static -> bool {
    return num_ > 0uz;
}};

constexpr auto isNotOriginCell{[] [[nodiscard]] (
    std::tuple<size_t, size_t> const coords_
) static -> bool {
    auto const [rowIdx, colIdx]{coords_};

    return isPositive(rowIdx) || isPositive(colIdx);
}};

constexpr auto isOpenBracket{[] [[nodiscard]] (char const bracket_) static -> bool {
    return bracket_ == kOpenBracket;
}};

constexpr auto isCloseBracket{[] [[nodiscard]] (char const bracket_) static -> bool {
    return bracket_ == kCloseBracket;
}};

constexpr auto mergeRecords{[] [[nodiscard]] (
    dpBalanceRec const acummRec_,
    dpBalanceRec const currRec_
) static -> dpBalanceRec {
    return acummRec_ | currRec_;
}};

constexpr auto incrementRecord{[] [[nodiscard]] (
    dpBalanceRec const rec_,
    size_t const delta_
) static -> dpBalanceRec {
    return rec_ << delta_;
}};

constexpr auto decrementRecord{[] [[nodiscard]] (
    dpBalanceRec const rec_,
    size_t const delta_
) static -> dpBalanceRec {
    return rec_ >> delta_;
}};

} // namespace

class Solution {
public:
    [[nodiscard]]
    static auto hasValidPath(std::vector<std::vector<char>> const & grid_) -> bool;
};

auto Solution::hasValidPath(std::vector<std::vector<char>> const & grid_) -> bool {
    // 1. Return immediately if the grid layout contains no traversable cells.
    if (grid_.empty() || grid_.front().empty()) {
        return kPathNotFound;
    }

    auto const rowTot   {grid_.size()};
    auto const colTot   {grid_.front().size()};
    auto const pathLen  {rowTot + colTot - 1uz};

    // 2. Reject paths with odd length or mismatched boundary parenthesis types.
    if (auto const  firstCellBracket{grid_.front().front()},
                    lastCellBracket {grid_.back().back()};
        isOdd(pathLen) ||
        isCloseBracket(firstCellBracket) || isOpenBracket(lastCellBracket)
    ) {
        return kPathNotFound;
    }

    // 3. Initialize dynamic programming state vector to track reachable balances.
    auto dpBalanceRecs{std::vector<dpBalanceRec>(colTot)};
    dpBalanceRecs.front().set(kInitBalance);

    auto rowsIdxs   {   vs::iota(0uz, rowTot)};
    auto colsIdxs   {   vs::iota(0uz, colTot)};
    // 4. Generate all valid traversal coordinates excluding the origin point.
    auto coords     {   vs::cartesian_product(rowsIdxs, colsIdxs) |
                        vs::filter(isNotOriginCell)};

    // 5. Traverse coordinates sequentially to accumulate valid path balances.
    for(auto const [rowIdx, colIdx]: coords) {
        // Aggregate allowable balance states flowing from the top or left cells.
        auto nextDpBalanceRec{dpBalanceRec{}};

        if(isPositive(rowIdx)) {
            auto const aboveCellDpBalanceRec{dpBalanceRecs[colIdx]};
            nextDpBalanceRec = mergeRecords(nextDpBalanceRec, aboveCellDpBalanceRec);
        }

        if(isPositive(colIdx)) {
            auto const leftCellDpBalanceRec{dpBalanceRecs[colIdx - 1uz]};
            nextDpBalanceRec = mergeRecords(nextDpBalanceRec, leftCellDpBalanceRec);
        }

        auto const  bracket             {grid_[rowIdx][colIdx]};
        auto &      updatedDpBalanceRec {dpBalanceRecs[colIdx]};
        // 6. Shift accumulated balances based on parenthesis at the current cell.
        updatedDpBalanceRec = isOpenBracket(bracket) ?
            incrementRecord(nextDpBalanceRec, kBalanceDelta) :
            decrementRecord(nextDpBalanceRec, kBalanceDelta);
    }

    // 7. Check if a perfect zero balance remains achievable at the final destination.
    auto const isPathFound{dpBalanceRecs.back().test(kValidBalanceIdx)};
    return isPathFound;
}
