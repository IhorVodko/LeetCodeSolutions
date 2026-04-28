// problem : https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/description
// submission : https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/submissions/1990327127
// solution post : https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/solutions/8109080/
//        c-modern-readable-code-beats-100-runtime-tfnr

// Approach : Linear Cost Shift (Median Optimization)
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' by 'm' be the grid size
// 'k' - given subtrahend
// 'r' - range between minimum and maximum numbers
// 'V' - maximum possible number (capped at 10'000)
// complexity :  O(n * m + r / k) 
// complexity : O(V) 

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

class Solution final {
public:
    using arr2T =  std::vector<std::vector<int>>;

    // Function to calculate the minimum operations to make all numbers equal.
    [[nodiscard]]
    auto minOperations(
        arr2T const & grid_,
        int const subtrahend_
    ) const -> int;

private:
    // Maximum possible value in the grid as per problem constraints.
    static auto constexpr kMaxNum{10'000};
};

auto Solution::minOperations(
    arr2T const & grid_,
    int const subtrahend_
) const -> int {
    namespace vs = std::views;
    using intLim = std::numeric_limits<int>;

    // Frequency array to count occurrences of each number up to kMaxNum.
    auto numCnts{std::vector<int>(kMaxNum + 1)};
    auto minNum{intLim::max()};
    auto maxNum{intLim::min()};

    for(auto const firstNum{grid_.front().front()}; auto const & row: grid_) {
        for(auto const num: row) {
            if((num - firstNum) % subtrahend_ != 0) {
                // Impossible to make all numbers equal.
                return -1;
            }

            ++numCnts[num];
            minNum = std::min(minNum, num);
            maxNum = std::max(maxNum, num);
        }
    }

    auto opCnt{0};

    // Calculate operations to make all numbers equal to minNum.
    for(auto num{minNum + subtrahend_}; num <= maxNum; num += subtrahend_) {
        // Operations for the current number to reach minNum.
        auto const currOpCnt{(num - minNum) / subtrahend_ * numCnts[num]};

        opCnt += currOpCnt;
        // Update frequency array to be a prefix frequency array.
        numCnts[num] += numCnts[num - subtrahend_];
    }

    // Total count of numbers in the grid
    auto const numsCnt{numCnts[maxNum]};

    // Iterate again to find absolute minimum operations across all valid targets.
    for (auto num{minNum + subtrahend_}; num <= maxNum; num += subtrahend_) {
        auto const smallerNumsCnt{numCnts[num - subtrahend_]};
        auto const largerNumsCnt{numsCnt - smallerNumsCnt};
        // Adjust opCnt: add count of smaller numbers, subtract count of larger numbers.
        auto const currOpCnt{opCnt + smallerNumsCnt - largerNumsCnt};

        opCnt = std::min(opCnt, currOpCnt);
    }

    // Return the minimum operations calculated
    return opCnt;
}
