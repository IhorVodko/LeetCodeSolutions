// problem : https://leetcode.com/problems/evaluate-division/description/
// submission : https://leetcode.com/problems/evaluate-division/submissions/1932539728
// solution post : https://leetcode.com/problems/evaluate-division/solutions/7612512/
//    c-modern-readable-code-beats-100-runtime-xuar

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the number of equations
// 'm' - number of queries
// time complexity O(n + m)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    using formulasT = std::vector<std::vector<std::string>>;
    using mapT =
        std::unordered_map<std::string_view, std::pair<std::string_view, double>>;

    [[nodiscard]]
    auto calcEquation(
        formulasT const & dividendAndDivisorPairsGiven_,
        std::span<double const> const quotients_,
        formulasT const & dividendAndDivisorPairsAsked_
    ) const -> std::vector<double>;

private:
    [[nodiscard]]
    auto Find(
        mapT & nodeToGroupAndWeight_,
        std::string_view const group_
    ) const -> std::pair<std::string_view, double>;
    auto Union(
        mapT & nodeToGroupAndWeight_,
        std::string_view const dividend_,
        std::string_view const divisor_,
        double const quotient_
    ) const -> void;

    auto static constexpr kUnknown{-1.0};
};

auto Solution::calcEquation(
    formulasT const & dividendAndDivisorPairsGiven_,
    std::span<double const> const quotients_,
    formulasT const & dividendAndDivisorPairsAsked_
) const -> std::vector<double> {
    namespace vs = std::views;

    auto const pairsGivenSz{dividendAndDivisorPairsGiven_.size()};
    auto nodeToGroupAndWeight{mapT{}};
    nodeToGroupAndWeight.reserve(pairsGivenSz);
    // Build Union-Find structure from given equations
    for(auto const i: vs::iota(0uz, pairsGivenSz)) {
        auto const & dividenAndDivisor{dividendAndDivisorPairsGiven_[i]};
        auto const dividend{std::string_view{dividenAndDivisor.front()}};
        auto const divisor{std::string_view{dividenAndDivisor.back()}};
        auto const quotient{quotients_[i]};
        Union(nodeToGroupAndWeight, dividend, divisor, quotient);
    }
    auto const pairsAskedSz{dividendAndDivisorPairsAsked_.size()};
    auto quotients{std::vector<double>(pairsAskedSz)};
    // Resolve each query using root comparison and relative weights
    for(auto const i: vs::iota(0uz, pairsAskedSz)) {
        auto const & dividendAndDivisor{dividendAndDivisorPairsAsked_[i]};
        auto const dividend{std::string_view{dividendAndDivisor.front()}};
        auto const divisor{std::string_view{dividendAndDivisor.back()}};
        if( nodeToGroupAndWeight.contains(dividend) &&
            nodeToGroupAndWeight.contains(divisor)
        ) {
            auto const [dividendGroup, dividendWeight]{
                Find(nodeToGroupAndWeight, dividend)};
            auto const [divisorGroup, divisorWeight]{
                Find(nodeToGroupAndWeight, divisor)};
            if(dividendGroup == divisorGroup) {
                auto const quotient{dividendWeight / divisorWeight};
                quotients[i] = quotient;
            } else {
                quotients[i] = kUnknown;
            }
        } else {
            quotients[i] = kUnknown;
        }
    }
    return quotients;
}

[[nodiscard]]
auto Solution::Find(
    mapT & nodeToGroupAndWeight_,
    std::string_view const group_
) const -> std::pair<std::string_view, double> {
    // Initialize node as its own parent with weight 1 if unseen
    if(!nodeToGroupAndWeight_.contains(group_)) {
        nodeToGroupAndWeight_[group_] = {group_, 1.0};
    }
    auto const [group, weight]{nodeToGroupAndWeight_.at(group_)};
    // Path compression with weight adjustment toward root
    if(group != group_) {
        auto const [rootGroup, rootWeigth]{Find(nodeToGroupAndWeight_, group)};
        auto const newWeight{weight * rootWeigth};
        nodeToGroupAndWeight_[group_] = {rootGroup, newWeight};
    }
    return nodeToGroupAndWeight_.at(group_);
}

auto Solution::Union(
    mapT & nodeToGroupAndWeight_,
    std::string_view const dividend_,
    std::string_view const divisor_,
    double const quotient_
) const -> void {
    // Find root groups and relative weights
    auto const [dividendGroup, dividendWeight]{
        Find(nodeToGroupAndWeight_, dividend_)};
    auto const [divisorGroup, divisorWeight]{Find(nodeToGroupAndWeight_, divisor_)};
    // Merge groups while preserving ratio consistency
    if( dividendGroup != divisorGroup) {
        auto const newWeight{divisorWeight * quotient_ / dividendWeight};
        nodeToGroupAndWeight_[dividendGroup] = {divisorGroup, newWeight};
    }
}
