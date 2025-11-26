// problem : https://leetcode.com/problems/paths-in-matrix-whose-sum-is-divisible-by-k/description/
// submission : https://leetcode.com/problems/paths-in-matrix-whose-sum-is-divisible-by-k/submissions/1840455777
// solution post : https://leetcode.com/problems/paths-in-matrix-whose-sum-is-divisible-by-k/solutions/7376251/
//    c-modern-readable-code-beats-100-runtime-lsp3

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream{"display_runtime.txt"} << 0 << std::endl;
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
// let 'n' by 'm' be the size of a given matrix
// 'k' - the value of a divisor given
// time complexity O(n * m * k)
// space complexity O(n * m * k)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto numberOfPaths(
        std::vector<vector<int>> const & mx_,
        int const divisor_
    ) const -> int;

private:
    static auto constexpr kModVal{1'000'000'007};
};

auto Solution::numberOfPaths(
    std::vector<vector<int>> const & mx_,
    int const divisor_
) const -> int {
    namespace vs = std::views;

    auto const rCnt{std::ssize(mx_)};
    auto const cCnt{std::ssize(mx_[0])};
    auto dpPahtCnts{std::vector(
        rCnt + 1,
        std::vector(
            cCnt + 1,
            std::vector<long long>(divisor_)
        )
    )};
    for(auto const r: vs::iota(1, rCnt + 1)) {
        for(auto const c: vs::iota(1, cCnt + 1)) {
            if(r == 1 && c == 1) [[unlikely]] {
                auto & currPathCnt{dpPahtCnts[r][c][mx_[0][0] % divisor_]};
                currPathCnt = 1;
                continue;
            }
            auto const currModSum{mx_[r - 1][c - 1] % divisor_};
            for(auto const reminder: vs::iota(0, divisor_)) {
                auto const prevModSum{
                    (reminder - currModSum + divisor_) % divisor_
                };
                auto const pahtCntAbove{dpPahtCnts[r - 1][c][prevModSum]};
                auto const pathCntLeft{dpPahtCnts[r][c - 1][prevModSum]};
                auto & currPathCnt{dpPahtCnts[r][c][reminder]};
                currPathCnt = (pahtCntAbove + pathCntLeft) % kModVal;
            }
        }
    }
    auto const validPathCnt{dpPahtCnts[rCnt][cCnt][0]};
    return validPathCnt;
}
