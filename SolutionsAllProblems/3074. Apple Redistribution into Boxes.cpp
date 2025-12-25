// problem : https://leetcode.com/problems/apple-redistribution-into-boxes/description
// submission : https://leetcode.com/problems/apple-redistribution-into-boxes/submissions/1864872617
// solution post : https://leetcode.com/problems/apple-redistribution-into-boxes/solutions/7437854/
//    c-modern-readable-code-beats-100-runtime-ygko

// import std;

// let 'n' be the number of packs
// 'm' - of boxes
// time complexity O(n + m * log(m))
// space complexity O(m)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
// compute a minimum number of boxes required to redistribute 'packs_' of apples
// into boxes of capacities 'boxes_'
    [[nodiscard]]
    auto minimumBoxes(
        std::span<int const> const packs_,
        std::span<int const> const boxes_
    ) const -> int;
};

auto Solution::minimumBoxes(
    std::span<int const> const packs_,
    std::span<int const> const boxes_
) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto appleTotCnt{rngs::fold_left(packs_, 0, std::plus{})};
    auto boxPqMax{std::priority_queue<int>{boxes_.begin(), boxes_.end()}};
    auto boxMinCnt{0};
    // greedily take boxes with maximum capacity untill all apples are distributed
    do {
        ++boxMinCnt;
        appleTotCnt -= boxPqMax.top();
        boxPqMax.pop();
    } while(appleTotCnt > 0 && !boxPqMax.empty());
    return boxMinCnt;
}
