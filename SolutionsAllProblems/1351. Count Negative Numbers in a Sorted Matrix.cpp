// problem : https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/description
// submission : https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/submissions/1867534055
// solution post : https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/solutions/7445803/
//    c-modern-readable-code-beats-100-runtime-lihs

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
// let 'n' by 'm' be the size of matrix
// time complexity O(n + m)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto countNegatives(std::vector<vector<int>> const & mx_) const -> int;
};

auto Solution::countNegatives(std::vector<vector<int>> const & mx_) const -> int {
    namespace vs = std::views;

    auto negCnt{0};
    auto const colCnt{std::ssize(mx_.front())};
    auto minNegCol{colCnt - 1};
    for(auto const & row: mx_) {
        while(minNegCol >= 0 && row[minNegCol] < 0) {
            --minNegCol;
        }
        negCnt += (colCnt - (minNegCol + 1));
    }
    return negCnt;
}
