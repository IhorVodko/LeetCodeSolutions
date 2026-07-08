// problem : https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-ii/description
// submission : https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-ii/submissions/2060912248
// solution post : https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-ii/solutions/8384829/
//    modern-readable-code-optimal-time-comple-tq4l

// Approach : Prefix Arrays with Modular Arithmetic
// Runtime : 20 ms, beats 96.89 %

// Complexity analysis
// let 'n' be the string length
// 'm' - number of queries
//
// Note: We consider the precomputation step as O(1) time and space because its size is bounded by a hardcoded constant,
// independent of the input size.
//
// Time :  O(n)
// Space : O(1)

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

using ll = long long;

auto constexpr kModVal{1'000'000'007};
auto constexpr kMaxStrLen{100'005};
auto constexpr kRadix{10};
auto constexpr kFirstDigitChr{'0'};


// Precompute modular powers of 10 for range shifts
auto const kPows10{[] {
        auto pows10{std::array<ll, kMaxStrLen>{}};

        rs::generate(pows10, [next = 1ll] mutable {
            auto const curr{next};
            next = (next * kRadix) % kModVal;

            return curr;
        });

        return pows10;
}()};

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
    static auto sumAndMultiply(
        std::string_view const numStr_,
        std::vector<std::vector<int>> const & queries_
    ) -> std::vector<int>;
};

auto Solution::sumAndMultiply(
    std::string_view const numStr_,
    std::vector<std::vector<int>> const & queries_
) -> std::vector<int> {
    auto const numStrLen{std::ssize(numStr_)};

    // O(1) query resolution prefix data
    auto prefValues(std::vector(numStrLen + 1, 0ll));
    auto prefNonZeroCnts{std::vector(numStrLen + 1, 0)};
    auto prefDigitSums{std::vector(numStrLen + 1, 0)};

    for(auto const idxs{vs::iota(0, numStrLen + 1)};
        auto const [currIdx, nextIdx]: vs::zip(idxs, idxs | vs::drop(1))
    ) {
        auto const digit{numStr_[currIdx] - kFirstDigitChr};

        prefValues[nextIdx] = digit != 0 ?
            (prefValues[currIdx] * kRadix + digit) % kModVal :
            prefValues[currIdx];
        prefNonZeroCnts[nextIdx] = prefNonZeroCnts[currIdx] + (digit > 0 ? 1 : 0);
        prefDigitSums[nextIdx] = prefDigitSums[currIdx] + digit;
    }

    auto const solve{[&] (auto const & query_) {
        auto const firstIdx{query_[0]};
        auto const lastIdx{query_[1]};
        auto const nonZeroCnt{prefNonZeroCnts[lastIdx + 1] - prefNonZeroCnts[firstIdx]};
        auto const digitSum{prefDigitSums[lastIdx + 1] - prefDigitSums[firstIdx]};
        // Align left boundary to its place magnitude in the current range
        auto const subtractedOffset{prefValues[firstIdx] * kPows10[nonZeroCnt]};
        
        auto concatenatedVal{(prefValues[lastIdx + 1]- subtractedOffset) % kModVal};
        // Normalize negative modulo
        if(concatenatedVal < 0) {
            concatenatedVal += kModVal;
        }

        return static_cast<int>((concatenatedVal * digitSum) % kModVal);
    }}; 
    
    return queries_ | vs::transform(solve) | rs::to<vector<int>>();
}
