// problem : https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-i/description/
// submission : https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-i/submissions/2059388105
// solution post : https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-i/solutions/8382302/
//    c-modern-readable-code-optimal-time-comp-69zw

// Approach : Mathematical Digit Filtering and Reconstruction
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the given number
// Time :  O(log(n))
// Space : O(1)

// import std;

namespace {

auto constexpr kRadix{10};

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
    static auto sumAndMultiply(int num_) -> long long;
};

auto Solution::sumAndMultiply(int num_) -> long long {
    auto placeValue{1ll};
    auto x{0ll};
    auto sum{0ll};
    
    while(num_ > 0) {
        auto const [newNum, digit]{std::div(num_, kRadix)};
        num_ = newNum;

        // Skips zero digits to concatenate the remaining digits properly
        if(digit == 0) {
            continue;
        }

        x += digit * placeValue;  
        sum += digit;
        placeValue *= kRadix;
    }

    return x * sum;
}
