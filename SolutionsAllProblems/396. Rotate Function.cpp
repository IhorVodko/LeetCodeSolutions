// problem : https://leetcode.com/problems/rotate-function/description
// submission : https://leetcode.com/problems/rotate-function/submissions/1992741454
// solution post : https://leetcode.com/problems/rotate-function/solutions/8125313/c-modern-readable-code-beats-100-runtime-3ufx

// Approach : Mathematical Derivation / Iterative State Transition
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the length of the array of numbers
// complexity :  O(n)
// complexity : O(1)

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
    [[nodiscard]]
    auto maxRotateFunction(std::vector<int> & nums_) const -> int;
};

auto Solution::maxRotateFunction(std::vector<int> & nums_) const -> int {
    namespace vs = std::views;

    auto currFuncRes{0};
    auto sum{0};
    auto const numsSz{static_cast<int>(nums_.size())};

    // Calculate initial sum and F(0) values
    for(auto const j: vs::iota(0, numsSz)) {
        auto const num{nums_[j]};

        currFuncRes += j * num;
        sum += num;
    }

    auto maxFuncRes{currFuncRes};
    
    // Loop over the array to compute F(k) iteratively
    for(auto const j: vs::iota(0, numsSz)) {
        // Calculate the delta to transition from F(k-1) to F(k).
        // 'nums_[numsSz - j - 1]' is the element wrapping around from the end of the
        // array to index 0. We subtract (n * 'this element') to correct its multiplier
        // from 'n' to 0.
        auto const delta{sum - numsSz * nums_[numsSz - j - 1]};

        currFuncRes += delta;
        maxFuncRes = std::max(maxFuncRes, currFuncRes);
    }

    return maxFuncRes;
}
