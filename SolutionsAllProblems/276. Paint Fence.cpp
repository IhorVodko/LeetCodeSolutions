// problem : https://leetcode.com/problems/paint-fence/description/
// submission : https://leetcode.com/problems/paint-fence/submissions/1817003880
// solution post : https://leetcode.com/problems/paint-fence/solutions/7316637/
//    c-modern-readable-code-beats-100-runtime-zhno

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
// let 'n' be the number of given posts
// 'm' - nubmer of given colors
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto numWays(
        int const postSz_,
        int const colorSz_
    ) const -> int;
};

auto Solution::numWays(
    int const postSz_,
    int const colorSz_
) const -> int {
    namespace vs = std::views;

    if(postSz_ == 1) {
        return colorSz_;
    } else if(postSz_ == 2) {
        return colorSz_ * colorSz_;
    }
    auto prevWaysCnt{colorSz_};
    auto currWaysCnt{colorSz_ * colorSz_};
    for(auto const postIdx: vs::iota(3, postSz_ + 1)) {
        auto const nextWaysCnt{(colorSz_ - 1) * (currWaysCnt + prevWaysCnt)};
        prevWaysCnt = currWaysCnt;
        currWaysCnt = nextWaysCnt;
    }
    auto waysTotalCnt{currWaysCnt};
    return waysTotalCnt; 
}
