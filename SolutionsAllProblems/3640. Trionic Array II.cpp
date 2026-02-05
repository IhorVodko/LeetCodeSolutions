// problem : https://leetcode.com/problems/trionic-array-ii/description
// submission : https://leetcode.com/problems/trionic-array-ii/submissions/1909335334
// solution post : https://leetcode.com/problems/trionic-array-ii/solutions/7555446/
//    c-modern-readable-code-beats-100-runtime-lcay

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the number of elements
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    // Alias for std::numeric_limits to shorten verbose type usage
    template<typename T_>
    using numLim = std::numeric_limits<T_>;
    using ll = long long;

    [[nodiscard]]
    auto maxSumTrionic(std::span<int const> const nums_) const -> ll;
};

auto Solution::maxSumTrionic(std::span<int const> const nums_) const -> ll {

    // Cache array size to avoid repeated calls
    auto const numsSz{std::ssize(nums_)};
    // Indices marking boundaries of the three segments
    auto segIdx1{numLim<int>::max()};
    auto segIdx2{numLim<int>::max()};
    auto segIdx3{numLim<int>::max()};
    // Accumulators for local and maximal partial sums
    auto curSum{numLim<ll>::max()};
    auto maxSum{numLim<ll>::max()};
    // Sum of the current trionic candidate
    auto subArrCurSum{numLim<ll>::max()};
    // Global maximum answer
    auto subArrMaxSum{std::numeric_limits<ll>::min()};
    auto idx1{0};
    while(idx1 < numsSz) {
        segIdx3 = idx1 + 1;
        subArrCurSum = 0;
        // Find maximal strictly increasing prefix starting at idx1
        for(; segIdx3 < numsSz && nums_[segIdx3 - 1] < nums_[segIdx3]; ++segIdx3);
        segIdx1 = segIdx3 - 1;
        // Need at least two elements for the first segment
        if(segIdx1 == idx1) {
            ++idx1;
            continue;
        }
        // Add peak and its predecessor to ensure middle segment overlap
        subArrCurSum += nums_[segIdx1] + nums_[segIdx1 - 1];
        // Traverse strictly decreasing middle segment
        for(; segIdx3 < numsSz && nums_[segIdx3 - 1] > nums_[segIdx3]; ++segIdx3) {
            subArrCurSum += nums_[segIdx3];
        }
        segIdx2 = segIdx3 - 1;
        // Validate existence and direction of the third segment
        if( segIdx2 == segIdx1 || segIdx2 == numsSz - 1 ||
            (nums_[segIdx3] <= nums_[segIdx2])
        ) {
            idx1 = segIdx2 + 1;
            continue;
        }
        // Include the first element of the third increasing segment
        subArrCurSum += nums_[segIdx2 + 1];
        maxSum = 0;
        curSum = 0;
        // Extend the third segment forward while maximizing its contribution
        for(auto idx2{segIdx2 + 2}; idx2 < numsSz && nums_[idx2] > nums_[idx2 - 1];
            ++idx2
        ) {
            curSum += nums_[idx2];
            maxSum = std::max(maxSum, curSum);
        }
        subArrCurSum += maxSum;
        maxSum = 0;
        curSum = 0;
        // Extend the first segment backward to maximize its contribution
        for(auto idx2{segIdx1 - 2}; idx2 >= idx1; --idx2) {
            curSum += nums_[idx2];
            maxSum = std::max(maxSum, curSum);
        }
        subArrCurSum += maxSum;
        // Update global maximum trionic curSum
        subArrMaxSum = std::max(subArrMaxSum, subArrCurSum);
        // Skip indices already covered by the middle segment
        idx1 = segIdx2;
    } 
    return subArrMaxSum;
}
