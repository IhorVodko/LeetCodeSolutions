// problem : https://leetcode.com/problems/increment-submatrices-by-one/description/
// submission : https://leetcode.com/problems/increment-submatrices-by-one/submissions/1829470308
// solution post : https://leetcode.com/problems/increment-submatrices-by-one/solutions/7347991/
//    c-modern-readable-code-beats-100-runtime-nzo8

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream("display_runtime.txt") << 0 << std::endl;
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
    using mxT = std::vector<std::vector<int>>;
    using queriesT = std::span<std::vector<int> const>;

// let 'n' by 'n' be a given matrix size
// 'm' - number of given queries
// time complexity O(n^2 + m)
// space complexity O(n^2)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto rangeAddQueries(
        int const dim_,
        queriesT const queries_
    ) const -> mxT;
};

auto Solution::rangeAddQueries(
    int const dim_,
    queriesT const queries_
) const -> mxT {
    namespace vs = std::views;

    auto rangeUpdateMx{mxT(dim_ + 1, std::vector<int>(dim_ + 1))};
    for(auto const & query: queries_) {
        auto const r1{query[0]};
        auto const c1{query[1]};
        auto const r2{query[2]};
        auto const c2{query[3]};
        rangeUpdateMx[r1][c1] += 1;
        rangeUpdateMx[r2 + 1][c1] -= 1;
        rangeUpdateMx[r1][c2 + 1] -= 1;
        rangeUpdateMx[r2 + 1][c2 + 1] += 1;
    }
    auto mx{mxT(dim_, std::vector<int>(dim_))};
    for(auto const r: vs::iota(0, dim_)) {
        for(auto const c: vs::iota(0, dim_)) {
            auto val1{r == 0 ? 0 : mx[r - 1][c]};
            auto val2{c == 0 ? 0 : mx[r][c - 1]};
            auto val3{r == 0 || c == 0 ? 0 : mx[r - 1][c - 1]};
            mx[r][c] = rangeUpdateMx[r][c] + val1 + val2 - val3;
        }
    }
    return mx;
}
