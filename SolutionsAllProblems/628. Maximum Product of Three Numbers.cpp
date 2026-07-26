// problem : https://leetcode.com/problems/maximum-product-of-three-numbers/description
// submission : https://leetcode.com/problems/maximum-product-of-three-numbers/submissions/2082469527
// solution post : https://leetcode.com/problems/maximum-product-of-three-numbers/solutions/8422348/
//    simplanation-simple-explanation-by-cyber-z2kp

// Approach : Single-Pass Min-Max Tracking
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the cont of numbers
// Time :  O(n)
// Space : O(1)

// import std;

namespace {

auto constexpr kMinNum{std::numeric_limits<int>::min()};
auto constexpr kMaxNum{std::numeric_limits<int>::max()};

// Initializer to configure fast I/O before main() runs
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
    [[nodiscard]]
    static auto maximumProduct(std::vector<int> const & nums_) -> int;
};

auto Solution::maximumProduct(std::vector<int> const & nums_) -> int {
    // Track the two smallest numbers
    auto minFirst{kMaxNum};
    auto minSecond{kMaxNum};

    // Track the three largest numbers
    auto maxFirst{kMinNum}; 
    auto maxSecond{kMinNum};
    auto maxThird{kMinNum}; 

    for(auto const num : nums_) {
        // Update minimums
        if(num < minFirst) {
            minSecond = std::exchange(minFirst, num);
        } else {
            minSecond = std::min(minSecond, num);
        }

        // Update maximums
        if(num > maxFirst) {
            maxThird = maxSecond;
            maxSecond = std::exchange(maxFirst, num);
        } else if(num > maxSecond) {
            maxThird = std::exchange(maxSecond, num);
        } else {
            maxThird = std::max(maxThird, num);
        }
    }

    // The max product is either the three largest, or the two smallest (which might be
    // negative) and the single largest.
    return std::max(
        maxFirst * maxSecond * maxThird, 
        minFirst * minSecond * maxFirst
    );
}
