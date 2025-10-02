// problem : https://leetcode.com/problems/water-bottles-ii/description
// submission : https://leetcode.com/problems/water-bottles-ii/submissions/1789351133
// solution post : https://leetcode.com/problems/water-bottles-ii/solutions/7243246/
//    c-modern-readable-code-beats-100-runtime-y89t

// import std;

class Solution {
public:
// let 'n' be the nubmer of the given filled bottles
// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maxBottlesDrunk(
        int numBottles,
        int numExchange
    ) const -> int;

private:
    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
};

auto Solution::maxBottlesDrunk(
    int numBottles,
    int numExchange
) const -> int {
    auto const a{1};
    auto const b{(2 * numExchange) - 3};
    auto const c{-2 * numBottles};
    auto const discriminant{(b * b) - (4 * a * c)};
    auto const root{static_cast<int>(std::ceil(
            (-1 * b + std::sqrt(discriminant))
        /   (2.0 * a)
    ))};
    auto const consumedBottles{numBottles + root - 1};
    return consumedBottles;
}
