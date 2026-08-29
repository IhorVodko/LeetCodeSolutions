// problem : https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/description
// submission : https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/submissions/2124189875
// solution post : https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/solutions/8489659/
//    simplanation-simple-explanation-by-cyber-mxlg

// Approach : Connected Components via Sorting & Grouping
// Runtime : 120 ms, beats 93.24 %

// Complexity analysis
// let 'n' be the count of numbers
// Time :  O(n * log(n))
// Space : O(n)

// import std;

// #include <algorithm>
// #include <ios>
// #include <iostream>
// #include <iterator>
// #include <ranges>
// #include <vector>

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
    static auto lexicographicallySmallestArray(
        std::vector<int> nums_,
        int const diffLim_
    ) -> std::vector<int>;
};

auto Solution::lexicographicallySmallestArray(
    std::vector<int> nums_,
    int const diffLim_
) -> std::vector<int> {
    using numItT = std::vector<int>::iterator;

    auto const totNums{nums_.size()};

    // 1. Map iterators to original array elements to track their initial indices
    auto sortedNumIts{vs::iota(nums_.begin(), nums_.end()) | rs::to<std::vector>()};

    // 2. Sort iterators by target value to prepare contiguous swappable chunks
    rs::sort(sortedNumIts, {}, [] (auto const numIt_) { return *numIt_; });

    auto targetNumIts{std::vector<numItT>{}};
    targetNumIts.reserve(totNums);
    
    auto chunkNums{std::vector<int>{}};
    chunkNums.reserve(totNums);

    // 3. Partition sorted elements where adjacent values differ by no more than limit
    auto numItChunks{sortedNumIts | vs::chunk_by([=] (
            numItT const currNumIt_,
            numItT const nextNumIt_
        ) {
            return *nextNumIt_ - *currNumIt_ <= diffLim_;
        }
    )};

    // 4. Process each independent swappable component to place values optimally
    for(auto const numItChunk: numItChunks) {
        targetNumIts.clear();
        chunkNums.clear();

        // 5. Gather target memory locations and values for the current component
        for(auto const numIt: numItChunk) {
            targetNumIts.emplace_back(numIt);
            chunkNums.emplace_back(*numIt);
        }

        // 6. Sort iterators by memory address to find sequential original positions
        rs::sort(targetNumIts);
    
        // 7. Assign smallest available values to earliest available original positions
        for(auto const [targetNumIt, num]: vs::zip(targetNumIts, chunkNums)) {
            *targetNumIt = num;
        }
    }

    return nums_;
}
