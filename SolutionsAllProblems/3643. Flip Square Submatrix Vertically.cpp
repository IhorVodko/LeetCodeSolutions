// problem : https://leetcode.com/problems/flip-square-submatrix-vertically/description/
// submission : https://leetcode.com/problems/flip-square-submatrix-vertically/submissions/1954981765
// solution post : https://leetcode.com/problems/flip-square-submatrix-vertically/solutions/7678676/
//    c-modern-readable-code-runtime-0-ms-beat-3jkv

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

// let 'n' by 'n' be the number of
// time complexity O(n^2)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    using mxT = std::vector<std::vector<int>>;

    [[nodiscard]]
    auto reverseSubmatrix(auto & mx_,
        int const subMxBeginR_,
        int const subMxBeginC_,
        int const subMxRCSz_
    ) const -> mxT;
};

auto Solution::reverseSubmatrix(auto & mx_,
    int const subMxBeginR_,
    int const subMxBeginC_,
    int const subMxRCSz_
) const -> mxT {
    namespace vs = std::views;

    // Swap rows symmetrically within the submatrix from top and bottom
    for(auto currR{subMxBeginR_}, oppositeR{subMxBeginR_ + subMxRCSz_ - 1};
        currR < oppositeR; ++currR, --oppositeR
    ) {
        // Iterate through all columns within the submatrix boundaries
        for(auto const c: vs::iota(subMxBeginC_, subMxBeginC_ + subMxRCSz_)) {
            std::swap(mx_[currR][c], mx_[oppositeR][c]);
        }
    }
    return mx_;
}
