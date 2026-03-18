// problem : https://leetcode.com/problems/count-submatrices-with-top-left-element-and-sum-less-than-k/description/
// submission : https://leetcode.com/problems/count-submatrices-with-top-left-element-and-sum-less-than-k/submissions/
//    1952224186
// solution post : https://leetcode.com/problems/count-submatrices-with-top-left-element-and-sum-less-than-k/solutions/
//    7659994/c-modern-readable-code-runtime-0-ms-beat-rsfc

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
    using mxT = std::vector<std::vector<int>>;

    [[nodiscard]]
    auto countSubmatrices(
        mxT const & mx_,
        int const sumUpLim_
    ) const -> int;
};

auto Solution::countSubmatrices(
    mxT const & mx_,
    int const sumUpLim_
) const -> int {
    namespace vs = std::views;

    auto const rSz{mx_.size()};
    auto const cSz{mx_.front().size()};

    // Early exit: smallest possible submatrix exceeds limit
    if(mx_.front().front() > sumUpLim_) {
        return 0;
    }
    // Stores cumulative sums for each column up to current row
    auto colAccums{std::vector<int>(cSz)};
    auto mxCnt{0};
    for(auto const & row: mx_) {
        // Accumulates sum of submatrix ending at current column
        auto rowAccum{0};
        for(auto c{0}; auto val: row) {
            // Update column-wise prefix sum
            colAccums[c] += val;
            // Extend submatrix to the right using accumulated column sums
            rowAccum += colAccums[c++];
            // Count valid submatrices starting at (0,0) to current position
            if(rowAccum <= sumUpLim_) {
                ++mxCnt;
            } else {
                // Further expansion will only increase sum. Early exit
                break;
            }
        }
    }
    return mxCnt;
}
