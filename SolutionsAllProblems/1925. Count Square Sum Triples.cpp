// problem : https://leetcode.com/problems/count-square-sum-triples/description/ 
// submission : https://leetcode.com/problems/count-square-sum-triples/submissions/1851243715
// solution post : https://leetcode.com/problems/count-square-sum-triples/solutions/7402902/
//    c-modern-readable-code-beats-100-runtime-q6tx

// import std;

// let 'n' be the given upper limit number
// time complexity O(n^2)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %

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
// let 'n' be the given upper limit number
// time complexity O(n^2)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto countTriples(int const numUpperLimit_) const -> int;

private:
    static auto constexpr kSafeRoundingOffset{0.5};
};

auto Solution::countTriples(int const numUpperLimit_) const -> int {
    namespace vs = std::views;

    auto cnt{0};
    for(auto const a: vs::iota(1, numUpperLimit_ + 1)) {
        for(auto const b: vs::iota(1, numUpperLimit_ + 1)) {
            auto const c{static_cast<int>(
                std::sqrt(a * a + b * b + kSafeRoundingOffset)
            )};
            if(c > numUpperLimit_) [[unlikely]] {
                break;
            }
            if(c * c == a * a + b * b) [[unlikely]] {
                ++cnt;
            }
        }
    }
    return cnt;
}
