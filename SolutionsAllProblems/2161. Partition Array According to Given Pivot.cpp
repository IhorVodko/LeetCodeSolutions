// problem : https://leetcode.com/problems/partition-array-according-to-given-pivot/description
// submission : https://leetcode.com/problems/partition-array-according-to-given-pivot/submissions/2026702033
// solution post : https://leetcode.com/problems/partition-array-according-to-given-pivot/solutions/8322076/
//        c-modern-readable-code-beats-100-runtime-bssn

// Approach : Three-Pass Filtering (Stable Partition)
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the count of numbers
// Time :  O(n)
// Space : O(1), auxiliary space

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto pivotArray(
        std::vector<int> const & nums_,
        int const pivotNum_
    ) -> std::vector<int>;
};

auto Solution::pivotArray(
    std::vector<int> const & nums_,
    int const pivotNum_
) -> std::vector<int> {
    namespace vs = std::views;
    namespace rs = std::ranges;

    auto partitionedNums{std::vector<int>{}};
    partitionedNums.reserve(nums_.size());

    // Extract elements in three stable passes to preserve relative ordering
    rs::copy(
        nums_ | vs::filter([=] (auto const num_) { return num_ < pivotNum_; }),
        std::back_inserter(partitionedNums)
    );
    rs::copy(
        nums_ | vs::filter([=] (auto const num_) { return num_ == pivotNum_; }),
        std::back_inserter(partitionedNums)
    );
    rs::copy(
        nums_ | vs::filter([=] (auto const num_) { return num_ > pivotNum_; }),
        std::back_inserter(partitionedNums)
    );

    return partitionedNums;
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
