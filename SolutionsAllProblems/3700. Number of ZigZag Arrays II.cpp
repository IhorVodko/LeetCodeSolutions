// problem : https://leetcode.com/problems/number-of-zigzag-arrays-ii/description
// submission : https://leetcode.com/problems/number-of-zigzag-arrays-ii/submissions/2044760007
// solution post : https://leetcode.com/problems/number-of-zigzag-arrays-ii/solutions/8356235/c-modern-readable-code-optimal-time-comp-8jlb

// Approach : Fast Matrix Exponentiation
// Runtime : 283 ms, beats 81.40 %

// Complexity
// let 'n' be the zig-zag array length
// 'm' - number lower limit
// 'k' - number upper limit
// Time :  O((k - m)^3 * log(n))
// Space : O((k - m)^2)

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto zigZagArrays(
        int const zigZagLen_,
        int const numLowLim_, 
        int const numUpLim_
    ) -> int;
};

auto Solution::zigZagArrays(
    int const zigZagLen_,
    int const numLowLim_, 
    int const numUpLim_
) -> int {
    namespace rs = std::ranges;
    namespace vs = std::views;

    using vecT = std::vector<size_t>;
    using mxT = std::vector<vecT>;

    auto constexpr kMod{1'000'000'007};

    auto const rngLen_{numUpLim_ - numLowLim_ + 1};
    if(zigZagLen_ == 1) return rngLen_;

    auto constexpr ModAdd{[] (auto const val1_, auto const val2_) {
        return (val1_ + val2_) % kMod;
    }};

    // Vector-matrix mult: Computes new state vector by applying transition 
    // matrix to current state
    auto const Mult1{[&] (auto const & val1_, auto const & val2_) {
        auto prod{vecT(rngLen_)};
        for(auto const j: vs::iota(0, rngLen_)) {
            auto const prods{
                vs::iota(0, rngLen_) |
                vs::transform([&] (auto const j_) {
                    auto const val{static_cast<size_t>(val1_[j_])};
                    return (val * val2_[j_][j]) % kMod;
            })};
            prod[j] = rs::fold_left(prods, 0uz, ModAdd);
        }
        return prod;
    }};

    // Matrix-matrix mult: Squares transition matrix for fast exponentiation
    auto const Mult2{[&] (auto const & val1_, auto const & val2_) {
        auto prod{mxT(rngLen_, vecT(rngLen_))};
        for(auto const j1: vs::iota(0, rngLen_)) {
            for(auto const j2: vs::iota(0, rngLen_)) {
                auto prods{
                    vs::iota(0, rngLen_) |
                    vs::transform([&] (auto const j_) {
                        auto const val{static_cast<size_t>(val1_[j1][j_])};
                        return (val * val2_[j_][j2]) % kMod;
                })};
                prod[j1][j2] = rs::fold_left(prods, 0uz, ModAdd);
            }
        }
        return prod;
    }};

    // Build directional transition matrices. mxUp represents an UP step, mxDown
    // represents a DOWN step
    auto mxUp{mxT(rngLen_, vecT(rngLen_))};
    auto mxDown{mxT(rngLen_, vecT(rngLen_))};
    for(auto const j1: vs::iota(0, rngLen_)) {
        for(auto const j2: vs::iota(j1 + 1, rngLen_)) {
            mxUp[j1][j2] = 1;
            mxDown[j2][j1] = 1;
        }
    }

    // Pre-calculate a full 2-step cycle (UP then DOWN)
    auto mxUpDown{Mult2(mxUp, mxDown)};

    auto res{vecT(rngLen_, 1)};
    auto pow{zigZagLen_ - 1};

    // Save the odd state to apply the trailing half-cycle at the end
    auto const isOdd{pow % 2 == 1};
    
    // Halve the exponentiation space due to the pre-computed 2-step cycle
    pow /= 2;

    // Fast matrix exponentiation: Advances state logarithmically
    for(; pow > 0; pow /= 2) {
        if(pow % 2 == 1) res = Mult1(res, mxUpDown);
        if(pow > 1) mxUpDown = Mult2(mxUpDown, mxUpDown);
    }

    // Applied the trailing half-cycle (UP step) here to preserve order
    if(isOdd) {
        res = Mult1(res, mxUp);
    }

    // Sum all valid paths for unidirectional starts
    auto const zigZagTot{rs::fold_left(res, 0uz, ModAdd)};

    // Multiply by 2 since array of length > 1 can start with either up or down
    return static_cast<int>((2uz * zigZagTot) % kMod);
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
