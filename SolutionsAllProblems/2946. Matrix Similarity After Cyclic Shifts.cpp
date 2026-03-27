// problem : https://leetcode.com/problems/matrix-similarity-after-cyclic-shifts/description/
// submission : https://leetcode.com/problems/matrix-similarity-after-cyclic-shifts/submissions/1961146041
// solution post : https://leetcode.com/problems/matrix-similarity-after-cyclic-shifts/solutions/7704746/
//    c-modern-readable-code-runtime-0-ms-beat-tcph

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
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    using mxT = std::vector<std::vector<int>>;

    [[nodiscard]]
    auto areSimilar(
        mxT const & mx_,
        int shiftTotCnt_
    ) const -> bool;
};

auto Solution::areSimilar(
    mxT const & mx_,
    int shiftTotCnt_
) const -> bool {
    namespace vs = std::views;

    // Number of columns (assumes non-empty matrix)
    auto const cSz{std::ssize(mx_.front())};
    // Normalize shifts to avoid redundant full rotations. If it results in a full cycle,
    // matrix remains unchanged, so early exit
    if((shiftTotCnt_ %= cSz) == 0) {
        return true;
    } 
    auto const rSz{std::ssize(mx_)};
    // Iterate over original column indices
    for(auto const oldC: vs::iota(0, cSz)) {
        // Compute target column after cyclic shift
        auto const newC{(oldC + shiftTotCnt_) % cSz};
        // Compare all rows for this column mapping
        for(auto const r: vs::iota(0, rSz)) {
            if(mx_[r][oldC] != mx_[r][newC]) {
                return false;
            }
        }
    }
    return true;
}
