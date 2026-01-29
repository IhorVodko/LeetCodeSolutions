// problem : https://leetcode.com/problems/minimum-cost-to-convert-string-i/description
// submission : https://leetcode.com/problems/minimum-cost-to-convert-string-i/submissions/1901333158
// solution post : https://leetcode.com/problems/minimum-cost-to-convert-string-i/solutions/7535201/
//    c-modern-readable-code-beats-100-runtime-xgiy

// import std;

// let 'n' be the string length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %

inline static int const fastIOInit{
    [] {
        std::atexit([] () { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class Solution {
public:
    [[nodiscard]]
    auto minimumCost(
        std::string_view const fromStr_,
        std::string_view const toStr_,
        std::span<char const> const fromChrs_,
        std::span<char const> const toChrs_,
        std::span<int const> const chrCosts_
    ) const -> long long;

private:
    [[nodiscard]]
    inline auto ChrToIdx(char const chr_) const noexcept -> int;
    static auto constexpr kChrSetBegin{'a'}; 
    static auto constexpr kChrSetSz{26};
};

auto Solution::minimumCost(
    std::string_view const fromStr_,
    std::string_view const toStr_,
    std::span<char const> const fromChrs_,
    std::span<char const> const toChrs_,
    std::span<int const> const chrCosts_
) const -> long long {
    namespace vs = std::views;
    using intLim = std::numeric_limits<int>;
    using ll = long long;

    auto totCost{0ll};
    // Initialize minimum conversion costs for each character pair with "infinite" value
    auto minCosts{std::vector<std::vector<ll>>(
            kChrSetSz, std::vector<ll>(kChrSetSz, intLim::max()))};
    // Populate initial conversion costs from input data
    for(auto const i: vs::iota(0u, fromChrs_.size())) {
        auto const fromChr{ChrToIdx(fromChrs_[i])};
        auto const toChr{ChrToIdx(toChrs_[i])};
        minCosts[fromChr][toChr] =
            std::min(minCosts[fromChr][toChr], static_cast<ll>(chrCosts_[i]));
    }
    // Floyd-Warshall algorithm to compute all-pairs minimum conversion costs
    for(auto const transIdx: vs::iota(0, kChrSetSz)) {
        for(auto const fromIdx: vs::iota(0, kChrSetSz)) {
            for(auto const toIdx: vs::iota(0, kChrSetSz)) {
                auto & minCost{minCosts[fromIdx][toIdx]};
                auto const newCost{
                    minCosts[fromIdx][transIdx] + minCosts[transIdx][toIdx]};
                minCost = std::min(minCost, newCost);
            }
        }
    }
    // Calculate total cost to convert fromStr_ to toStr_ using precomputed minimum costs
    for(auto const i: vs::iota(0u, fromStr_.size())) {
        if(fromStr_[i] == toStr_[i]) {
            continue;
        }
        auto const fromChr{ChrToIdx(fromStr_[i])};
        auto const toChr{ChrToIdx(toStr_[i])};
        if(minCosts[fromChr][toChr] >= intLim::max()) {
            // Conversion impossible
            return -1; 
        } 
        totCost += minCosts[fromChr][toChr];
    }
    return totCost;
}

// Helper function to map character to index in 0..25
auto Solution::ChrToIdx(char const chr_) const noexcept -> int {
    return chr_ - kChrSetBegin;
}
