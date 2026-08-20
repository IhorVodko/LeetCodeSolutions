// problem : https://leetcode.com/problems/distribute-elements-into-two-arrays-i/description
// submission : https://leetcode.com/problems/distribute-elements-into-two-arrays-i/submissions/2114241759
// solution post : https://leetcode.com/problems/distribute-elements-into-two-arrays-i/solutions/8472873/
//  simplanation-simple-explanation-by-cyber-qnnr

// Approach : Bidirectional Array Population (In-Place Partitioning)
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the count of numbers
// Time :  O(n)
// Space : O(n)

// import std;

// #include <vector>
// #include <ranges>
// #include <algorithm>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto resultArray(std::vector<int> const & numsIn_) -> std::vector<int>;
};

auto Solution::resultArray(std::vector<int> const & numsIn_) -> std::vector<int> {
    // 1. Preallocate single unified array for both resulting partitions
    auto numsOut{std::vector<int>(numsIn_.size())};

    // 2. Track partition boundaries growing inwards from both ends
    auto pos1{numsOut.begin()};
    auto pos2{numsOut.rbegin()};

    // 3. Assign initial elements to establish the starting states
    *pos1 = numsIn_[0];
    *pos2 = numsIn_[1];

    // 4. Distribute elements based on comparison of last added values
    for(auto const num: numsIn_ | vs::drop(2)) {
        (*pos1 > *pos2 ? *++pos1 : *++pos2) = num;
    }

    // 5. Restore original sequential order of the second partition
    rs::reverse(++pos1, numsOut.end());

    return numsOut;
}
