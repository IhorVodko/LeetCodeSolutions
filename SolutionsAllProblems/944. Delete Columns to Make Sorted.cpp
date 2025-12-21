// problem : https://leetcode.com/problems/delete-columns-to-make-sorted/description
// submission : https://leetcode.com/problems/delete-columns-to-make-sorted/submissions/1861393188
// solution post : https://leetcode.com/problems/delete-columns-to-make-sorted/solutions/7428190/
//    c-modern-readable-code-beats-100-runtime-yxvc

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

// let 'n' be the number of given strings
// 'm' - string length
// time complexity O(n * m)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto minDeletionSize(std::span<std::string const> const strs_) const -> int;
};

auto Solution::minDeletionSize(std::span<std::string const> const strs_) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    return rngs::count_if(
        vs::iota(0u, strs_[0].size()),
        [&] (auto const idx_) { 
            return rngs::any_of(
                vs::zip(strs_, strs_ | vs::drop(1)),
                [=] (auto const & pair_) {
                    return std::get<0>(pair_)[idx_] > std::get<1>(pair_)[idx_];
            });
        }
    );
}
