// problem : https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/description
// submission : https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/submissions/2008308151
// solution post : https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/solutions/8281616/
//    c-modern-readable-code-beats-100-runtime-llv6

// Approach : Frequency Array Counting (O(N) Time)
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the length of each of the array of numbers
// 'M' - upper limit of the length of an array of numbers
// complexity :  O(n)
// complexity : O(M)

// import std;

class Solution final {
public:
    using numsT = std::vector<int>;

    [[nodiscard]]
    static auto findThePrefixCommonArray(
        numsT const & numsA_,
        numsT const & numsB_
    ) -> numsT;

private:
    // Max N bound from constraints
    static auto constexpr kMaxNumsSz{50};
};

auto Solution::findThePrefixCommonArray(
    numsT const & numsA_,
    numsT const & numsB_
) -> numsT {
    namespace vs = std::views;

    // Joint occurrence tracker
    auto numCounts{std::array<int, kMaxNumsSz + 1>{}};
    ++numCounts[numsA_.front()];
    ++numCounts[numsB_.front()];
    
    auto const numsSz{std::ssize(numsA_)};
    // Output prefix intersections
    auto commonPrefArr{std::vector<int>(numsSz, 0)};
    commonPrefArr.front() = numCounts[numsA_.front()] == 2 ? 1 : 0;

    // Process prefixes [1, N-1]
    for(auto const j: vs::iota(1, numsSz)) {
        commonPrefArr[j] = commonPrefArr[j - 1];
        // Pair found via array A
        if(++numCounts[numsA_[j]] == 2) {
            ++commonPrefArr[j];
        }
        // Pair found via array B
        if(++numCounts[numsB_[j]] == 2) {
            ++commonPrefArr[j];
        }
    }

    return commonPrefArr;
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
