// problem : https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-i/description/
// submission : https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-i/submissions/2172883377
// solution post : https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-i/solutions/8573666/
//    simplanation-simple-explanation-by-cyber-wdej

// Approach : Brute Force with Dynamic Distinct Counting
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the input array length
// Time :  O(n)
// Space : O(1)

// import std;

// #include <bitset>
// #include <iterator>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <vector>

namespace rs = std::ranges;
namespace vs = std::views;

namespace{

// Maximum possible element value per problem constraints
constexpr auto kMaxNum{100};

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
auto const fastIOInit{
    []{
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    }()
};


} // namespace

class Solution final{
public:
    [[nodiscard]]
    static auto sumCounts(std::vector<int> const & nums_) -> int;
};

auto Solution::sumCounts(std::vector<int> const & nums_) -> int {
    auto const numTot{std::ssize(nums_)};
    auto sum{0};

    // 1. Iterate over all possible subarray starting positions
    for(auto numMask{std::bitset<kMaxNum + 1>{}};
        auto const idx1: vs::iota(0, numTot)
    ){
        // Reset distinct element tracker for the new starting position
        numMask.reset();

        // 2. Extend subarray to the right and dynamically track unique elements
        for(auto uniqueCnt{0};
            auto const num: nums_ | vs::drop(idx1)
        ){
            // 3. Register newly discovered distinct elements
            if(!numMask.test(num)){
                numMask.set(num);
                ++uniqueCnt;
            }

            // 4. Accumulate the squared distinct count for the current subarray
            sum += uniqueCnt * uniqueCnt;
        }
    }
    
    return sum;
}
