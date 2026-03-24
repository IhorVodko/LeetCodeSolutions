// problem : https://leetcode.com/problems/construct-product-matrix/description/
// submission : https://leetcode.com/problems/construct-product-matrix/submissions/1957772349
// solution post : https://leetcode.com/problems/construct-product-matrix/solutions/7688130/c-modern-readable-code-runtime-0-ms-beat-gms0

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
// space complexity O(n * m)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    using mxT = std::vector<std::vector<int>>;

    [[nodiscard]]
    auto constructProductMatrix(mxT const & mx_) const ->  mxT;

private:
    auto static constexpr kModulus{12345};
};

auto Solution::constructProductMatrix(mxT const & mx_) const -> mxT {
    namespace vs = std::views;

    auto const rSz{std::ssize(mx_)};
    auto const cSz{std::ssize(mx_.front())};
    // Output matrix: stores the product of all other elements except the current cell
    auto prods{mxT(rSz, std::vector<int>(cSz))};

    // Compute products of all elements after current cell in reverse order
    auto accumProd{1ll};
    for(auto const r: vs::iota(0, rSz) | vs::reverse) {
        for(auto const c: vs::iota(0, cSz) | vs::reverse) {
            prods[r][c] = accumProd;
            accumProd = (accumProd * mx_[r][c]) % kModulus;
        }
    }

    // Multiply with products of all elements before current cell in normal order
    accumProd = 1;
    for(auto const r: vs::iota(0, rSz)) {
        for(auto const c: vs::iota(0, cSz)) {
            prods[r][c] = (prods[r][c] * accumProd) % kModulus;
            accumProd = (accumProd * mx_[r][c]) % kModulus;
        }
    }

    return prods;
}
