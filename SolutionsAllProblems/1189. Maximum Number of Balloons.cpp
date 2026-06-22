// problem : https://leetcode.com/problems/maximum-number-of-balloons/description
// submission : https://leetcode.com/problems/maximum-number-of-balloons/submissions/2042369897
// solution post : https://leetcode.com/problems/maximum-number-of-balloons/solutions/8352135/c-modern-readable-code-beats-100-runtime-yh41

// Approach : Frequency Counting and Bottleneck Analysis
// Runtime : 0 ms, beats 100.00 %


// Complexity
// let 'n' be the input string length
// Time :  O(n)
// Space : O(1)

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto maxNumberOfBalloons(std::string_view const source_) -> int;
};

auto Solution::maxNumberOfBalloons(std::string_view const source_) -> int {
    namespace vs = std::views;
    namespace rs = std::ranges;

    auto constexpr kTarget{"balloon"sv};
    auto constexpr kChrSetSz{26uz};
    auto constexpr kChrSetFirst{'a'};
    auto constexpr kChrSetLast{'z'};

    auto constexpr ToIdx{[] (auto const chr_) {
        assert(kChrSetFirst <= chr_ && chr_ <= kChrSetLast);

        return chr_ - kChrSetFirst;
    }};

    // Pre-compute target frequencies at compile time
    static auto constexpr cntPerChrTarget{[=] {
        auto cntPerChr{std::array<int, kChrSetSz>{}};
        for(auto const chr: kTarget) {
            ++cntPerChr[ToIdx(chr)];
        }
        return cntPerChr;
    }()};

    // Build frequency map for the input text
    auto cntPerChrSource{std::array<int, kChrSetSz>{}};
    for(auto const chr: source_) {
        ++cntPerChrSource[ToIdx(chr)];
    }
    
    // Find bottleneck character limiting maximum word formations
    auto targetCntUpLims{
        vs::iota(0uz, kChrSetSz) |
        vs::filter([] (auto const j_) { return cntPerChrTarget[j_] > 0; }) |
        vs::transform([&] (auto const j_) {
            return cntPerChrSource[j_] / cntPerChrTarget[j_];
        })
    };

    return rs::min(targetCntUpLims);
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
