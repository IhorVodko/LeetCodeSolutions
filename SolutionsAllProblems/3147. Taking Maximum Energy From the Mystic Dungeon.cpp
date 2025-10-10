// problem : https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon/description
// submission : https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon/submissions/1797191383
// solution post : https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon/solutions/7263939/
//    c-modern-readable-code-beats-100-runtime-8chk

// import std;

class Solution {
public:
// let 'n' be the number of the given energies
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maximumEnergy(
        std::vector<int> const & energies_,
        int const step_
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

auto Solution::maximumEnergy(
    std::vector<int> const & energies_,
    int const step_
) const -> int {
    namespace vs = std::views;
    using limitInt = std::numeric_limits<int>;

    if(energies_.empty()) {
        return limitInt::min();
    }
    auto const energiesSz{std::ssize(energies_)};
    auto maxEnergy{limitInt::min()};
    for(auto const idx: vs::iota(energiesSz - step_, energiesSz)) {
        auto currEnergy{0};
        for(auto const j:
            vs::iota(0, idx + 1) | vs::reverse | vs::stride(step_)
        ){
            currEnergy += energies_.at(j);
            maxEnergy = std::max(maxEnergy, currEnergy);
        }
    }
    return maxEnergy;
}
