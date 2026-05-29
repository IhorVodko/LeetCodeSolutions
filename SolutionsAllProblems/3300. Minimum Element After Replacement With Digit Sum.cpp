// problem : https://leetcode.com/problems/minimum-element-after-replacement-with-digit-sum/description
// submission : https://leetcode.com/problems/minimum-element-after-replacement-with-digit-sum/submissions/2016534583
// solution post : https://leetcode.com/problems/minimum-element-after-replacement-with-digit-sum/solutions/8301209/
//    c-modern-readable-code-beats-100-runtime-yjrq

// Approach : Functional Transformation and Lazy Evaluation
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the count of numbers
// 'M' - maximum number given
// complexity :  O(n * log(M))
// complexity : O(1)

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto minElement(std::vector<int> const & nums_) -> int;

private:
    // Constant base for decimal extraction
    static auto constexpr kRadix{10};
};

auto Solution::minElement(std::vector<int> const & nums_) -> int {
    namespace vs = std::views;
    namespace rs = std::ranges;

    auto const ComputeDigitSum{[] (auto num_) {
        auto sum{0};
        while(num_ > 0) {
            auto const [newNum, digit]{std::div(num_, kRadix)};
            sum += digit;
            num_ = newNum;
        }
        return sum;
    }};

    return rs::min(nums_ | vs::transform(ComputeDigitSum));
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
