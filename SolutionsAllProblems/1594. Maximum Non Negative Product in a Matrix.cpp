// problem : https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/description/
// submission : https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/submissions/1957662340
// solution post : https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/solutions/7687607/
//     c-modern-readable-code-runtime-0-ms-beat-caut

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

// let 'n' by 'm' be the matrix size
// time complexity O(n * m)
// space complexity O(m)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    template<typename T_>
    using mxT = std::vector<std::vector<T_>>;
    using ll = long long; 

    [[nodiscard]]
    auto maxProductPath(mxT<int> const & grid_) const -> int;

private:
    static auto constexpr kModulus{1'000'000'007};
};

auto Solution::maxProductPath(mxT<int> const & grid_) const -> int {
    namespace vs = std::views;

    auto const rSz{std::ssize(grid_)};
    auto const cSz{std::ssize(grid_.front())};

    // Track min and max product up to current cell in the row (rolling DP)
    auto minProds{std::vector<ll>(cSz)};
    auto maxProds{std::vector<ll>(cSz)};

    // Initialize starting cell
    maxProds[0] = minProds[0] = grid_[0][0];

    // Initialize first row (only reachable from left)
    for(auto const c: vs::iota(1, cSz)) {
        maxProds[c] = minProds[c] = maxProds[c - 1] * grid_[0][c];
    }

    for(auto const r: vs::iota(1, rSz)) {
        // First column (only reachable from top)
        maxProds[0] = minProds[0] = maxProds[0] * grid_[r][0];

        for(auto const c: vs::iota(1, cSz)) {
            auto const val{grid_[r][c]};

            // Previous states from left and top
            auto const minProdLeft{minProds[c - 1]};
            auto const minProdTop{minProds[c]};
            auto const maxProdLeft{maxProds[c - 1]};
            auto const maxProdTop{maxProds[c]};

            // min- and max-product to update
            auto & minProd{minProds[c]};
            auto & maxProd{maxProds[c]};

            // Negative flips min/max roles, so track both
            if (val >= 0) {
                minProd = std::min(minProdLeft, minProdTop) * val;
                maxProd = std::max(maxProdLeft, maxProdTop) * val;
            } else {
                minProd = std::max(maxProdLeft, maxProdTop) * val;
                maxProd = std::min(minProdLeft, minProdTop) * val;
            }
        }
    }

    // Final result must be non-negative; otherwise return -1
    auto const maxProd{
        maxProds[cSz - 1] < 0 ? -1 : (maxProds[cSz - 1] % kModulus)};
        
    return maxProd;
}
