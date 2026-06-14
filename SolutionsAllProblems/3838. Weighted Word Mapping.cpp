// problem : https://leetcode.com/problems/weighted-word-mapping/description
// submission : https://leetcode.com/problems/weighted-word-mapping/submissions/2033159641
// solution post : https://leetcode.com/problems/weighted-word-mapping/solutions/8334172/c-modern-readable-code-beats-100-runtime-n3td

// Approach : Modular Accumulation and Character Mapping
// Runtime : 0 ms, beats 100.00 %

// Complexity :
// let 'n' be the number of words
// 'm' - evarage word length
// Time :  O(n * m)
// Space : O(1)

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto mapWordWeights(
        std::vector<std::string> const & words,
        std::vector<int> const & weights
    ) -> std::string;

private:
    static auto constexpr kChrSetFirst{'a'};
    static auto constexpr kChrSetLast{'z'};
    static auto constexpr kChrSetSz{26};
};

auto Solution::mapWordWeights(
    std::vector<std::string> const& words,
    std::vector<int> const& weights
) -> std::string {
    namespace vs = std::views;
    namespace rs = std::ranges;

    static auto const MapBackwards{[] (auto const sum_) {
        return static_cast<char>(kChrSetLast - sum_);
    }};
    static auto const Sum{[&] (auto const accum_, auto const c_) {
        return (accum_ + weights[c_ - kChrSetFirst]) % kChrSetSz;
    }};
    static auto const ConvertToChr{[&] (auto const & w_) {
        auto const sum{rs::fold_left(w_, 0, Sum)};
        return MapBackwards(sum);
    }};

    return 
        words |
        vs::transform(ConvertToChr) |
        rs::to<std::string>();
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
