// problem : https://leetcode.com/problems/separate-the-digits-in-an-array/description/
// submission : https://leetcode.com/problems/separate-the-digits-in-an-array/submissions/2000567059
// solution post : https://leetcode.com/problems/separate-the-digits-in-an-array/solutions/8193322/
//    c-modern-readable-code-beats-100-runtime-mcjq

// Approach : Simulaiton via Reverse Processing and Final Reversal
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the count of given numbers
// 'M' - maximum of given numbers
// complexity :  O(n * log(M))
// complexity : O(1) auxiliary space

// import std;

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

class Solution final {
public:
    using numsT = std::vector<int>;

    [[nodiscard]]
    auto separateDigits(numsT const & nums_) const -> numsT;

private:
    auto Digitize(
        auto & digits_,
        auto num_
    ) const -> void;

    static auto const kRadix{10};
    static auto const kMaxDigitPerNum{6};
};

auto Solution::separateDigits(numsT const & nums_) const -> numsT {
    namespace vs = std::views; 
    namespace rngs = std::ranges;

    auto digits{numsT{}};
    digits.reserve(kMaxDigitPerNum * nums_.size());

    for(auto num: nums_ | vs::reverse) {
        Digitize(digits, num);
    }
    digits.shrink_to_fit();
    rngs::reverse(digits);

    return digits;
}

auto Solution::Digitize(
    auto & digits_,
    auto num_
) const -> void {
    while(num_ > 0) {
        auto const [quot, rem]{std::div(num_, kRadix)};
        // Append the extracted digit to the output vector
        digits_.emplace_back(rem);
        // Update the number with the remaining digits
        num_ = quot;
    }
}
