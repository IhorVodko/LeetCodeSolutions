// problem : https://leetcode.com/problems/sequential-digits/description
// submission : https://leetcode.com/problems/sequential-digits/submissions/2066531703
// solution post : https://leetcode.com/problems/sequential-digits/solutions/8395433/modern-readable-code-optimal-time-comple-xai0

// Approach : Precomputation and Filtering
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// We consider the precomputation step as O(1) time and space because its size is bounded by a hardcoded constant, independent of the input size.
// Time :  O(1)
// Space : O(1)

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

auto constexpr kRadix{10};
auto constexpr kMinLen{2};
// Total combinations from length 2 to 9 (8 + 7 + ... + 1)
auto constexpr kSeqDigitsNumTot{36};

// Precompute all valid sequential digit combinations at compile time in ascending order.
auto constexpr kSeqDigitsNums{[] {
    auto nums{std::array<int, kSeqDigitsNumTot>{}};
    auto idx{0uz};

    // Lengths of sequential numbers vary from 2 (e.g., 12) up to 9 (123456789).
    for(auto const len: vs::iota(kMinLen, kRadix)) {
        for(auto const start: vs::iota(1, kRadix - len + 1)) {
            auto num{0};
            for(auto const offset: vs::iota(0, len)) {
                num = num * kRadix + start + offset;
            }
            nums[idx++] = num;
        }
    }

    return nums;
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
    static auto sequentialDigits(
        int numLowLim_,
        int numUpLim_
    ) -> std::vector<int>;
};

auto Solution::sequentialDigits(
    int numLowLim_,
    int numUpLim_
) -> std::vector<int> {
    // Filter the generated sequence to match the requested numerical bounds
    return
        kSeqDigitsNums |
        vs::filter([=] (auto const num_) {
            return numLowLim_ <= num_ && num_ <= numUpLim_;
        }) |
        rs::to<std::vector>()
    ;
}
