// problem : https://leetcode.com/problems/minimum-xor-path-in-a-grid/description
// submission : https://leetcode.com/problems/minimum-xor-path-in-a-grid/submissions/2184105055
// solution post : https://leetcode.com/problems/minimum-xor-path-in-a-grid/solutions/8592930/simplanation-simple-explanation-by-cyber-9h1c

// Approach : Dynamic Programming with Bitmasking State Tracking
// Runtime : 146 ms, beats 85.95 %

// Complexity analysis
// let 'n' by 'm' be the given grid size
// 'k' - maximum xor sum (given by the problem constraints - 1024)
// Time :  O(n * m * k)
// Space : O(m * k)

// import std;

// #include <algorithm>
// #include <bitset>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <vector>
// #include <cstddef>

namespace rs = std::ranges;
namespace vs = std::views;

using vector2dT = std::vector<std::vector<int>>;

namespace {

// Problem constraints bound the max XOR value for grid paths
constexpr auto kMaxXor{std::size_t{1024}};
constexpr auto kAllXors{ vs::iota(0uz, kMaxXor)};
constexpr auto kError{-1};

using XorMaskT = std::bitset<kMaxXor>;

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace 

class Solution final {
public:
    static auto minCost(vector2dT const & grid_) -> int;
};

auto Solution::minCost(vector2dT const & grid_) -> int {
    if(grid_.empty() || grid_.front().empty()) {
        return 0;
    }

    auto const rowsTot{std::ssize(grid_)};
    auto const colsTot{std::ssize(grid_.front())};

    auto const rowIdxs{vs::iota(0, rowsTot)};
    auto const colsIdxs{vs::iota(0, colsTot)};
    // 1. Map all grid coordinates to process them sequentially
    auto const cells{vs::cartesian_product(rowIdxs, colsIdxs)};
    
    // 2. Initialize state tracker for XOR sums reaching current row cells
    auto xorDp{std::vector<XorMaskT>(colsTot)};
    xorDp.front().set(grid_.front().front());
    
    auto const isNotFirstCell{[] (auto const rowAndCol_) { 
        auto const [r, c]{rowAndCol_};
        return r > 0 || c > 0;
    }};

    // 3. Traverse coordinates applying transitions from left and top neighbors
    for(auto const [r, c]: cells | vs::filter(isNotFirstCell)) {
        const auto currVal{static_cast<std::size_t>(grid_[r][c])};
        auto currCellXorsWithoutVal{XorMaskT{}};
        
        if( auto const & topCellXors{xorDp[c]}; 
            r > 0
        ) {
            currCellXorsWithoutVal |= topCellXors;
        }
        
        if(c > 0) {
            auto const & leftCellXors{xorDp[c - 1]};
            currCellXorsWithoutVal |= leftCellXors;
        }
        
        auto currCellXorsWithVal{XorMaskT{}};
        auto const isReachable{[&currCellXorsWithoutVal] (auto const xor_) {
            return currCellXorsWithoutVal.test(xor_);
        }};
        
        // 4. Isolate the XOR sums that are viable prior to current cell
        auto reachableXorsWithoutVal{kAllXors | vs::filter(isReachable)};
        
        // 5. XOR current cell value with all viable preceding sums
        for(const auto reachableXor: reachableXorsWithoutVal) {
            currCellXorsWithVal.set(reachableXor ^ currVal);
        }
        
        // 6. Propagate updated XOR states into the active row memory
        xorDp[c] = currCellXorsWithVal;
    }

    // 7. Extract the smallest valid XOR sum terminating at the grid exit
    auto const minXorIt{rs::find_if(
        kAllXors,
        [&xorDp] (auto const xor_) {return xorDp.back().test(xor_); }
    )};
    auto const minXor{minXorIt == kAllXors.end() ? kError : static_cast<int>(*minXorIt)};

    return minXor;
}
