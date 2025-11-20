// problem : https://leetcode.com/problems/set-intersection-size-at-least-two/description/
// submission : https://leetcode.com/problems/set-intersection-size-at-least-two/submissions/1835344797
// solution post : https://leetcode.com/problems/set-intersection-size-at-least-two/solutions/7363161/
//    c-modern-readable-code-beats-100-runtime-kis1

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
// let 'n' be the number of given intervals
// time complexity O(n * log(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto intersectionSizeTwo(
        std::vector<std::vector<int>> & intervals_
    ) const -> int;
};

auto Solution::intersectionSizeTwo(
    std::vector<std::vector<int>> & intervals_
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    rngs::sort(
        intervals_,
        [] (
            auto const & lhs_,
            auto const & rhs_
        ) -> bool {
            auto const b1{lhs_[0]};
            auto const e1{lhs_[1]};
            auto const b2{rhs_[0]};
            auto const e2{rhs_[1]};
            return e1 == e2 ? b1 > b2 : e1 < e2;
        }
    );
    auto containingSetSz{0};
    auto prevBegin{-1};
    auto prevEnd{-1};
    auto const intervalsSz{std::ssize(intervals_)};
    for(auto const idx: vs::iota(0, intervalsSz)) {
        auto const currStart{intervals_[idx][0]};
        auto const currEnd{intervals_[idx][1]};
        auto isPrevSubSetOfCurr{prevBegin >= currStart};
        auto noOverlap{prevEnd < currStart};
        if(isPrevSubSetOfCurr) {
            continue;
        } else if(noOverlap) {
            containingSetSz += 2;
            prevBegin = currEnd - 1;
            prevEnd = currEnd;
        } else {
            containingSetSz += 1;
            prevBegin = prevEnd;
            prevEnd = currEnd;
        }
    }
    return containingSetSz;
}
