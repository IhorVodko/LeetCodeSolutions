// problem : https://leetcode.com/problems/brace-expansion-ii/description
// submission : https://leetcode.com/problems/brace-expansion-ii/submissions/2153094276
// solution post : https://leetcode.com/problems/brace-expansion-ii/solutions/8539824/simplanation-simple-explanation-by-cyber-2f3u

// Approach : Recursive Descent Parsing
// Runtime : 3 ms, beats 95.54 %

// Complexity analysis
// let 'n' be the input expression length
// 'm' - maximum nubmer of words present in the finale generated array
// 'l' - maximum length of a single generated array
// Time :  O(n + m * log(m) * l)
// Space : O(n + m * l)

// import std;

// #include <algorithm>
// #include <iostream>
// #include <iterator>
// #include <ranges>
// #include <string>
// #include <string_view>
// #include <vector>

// #include <cctype>
// #include <cstddef>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

using std::size_t;
using std::ptrdiff_t;
using std::string_literals::operator""s;

constexpr auto kComma{','};
constexpr auto kOpenBrace{'{'};
constexpr auto kCloseBrace{'}'};

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class Parser final {
public:
    explicit Parser(std::string_view expr_):
        mExpr{expr_},
        mExprLen{std::ssize(expr_)}
    {}

    [[nodiscard]]
    auto Parse() -> std::vector<std::string> {
        // 1. Evaluate expression as top-level union of terms.
        auto res{ParseUnion()};
        
        rs::sort(res);

        // 2. Remove duplicate generated strings.
        auto const uniqueRng{rs::unique(res)};
        res.erase(uniqueRng.begin(), uniqueRng.end());

        return res;
    }

private:
    [[nodiscard]]
    auto ParseUnion() -> std::vector<std::string> {
        // 3. Process the first set in a comma-separated list.
        auto unionRes{parseConcatenation()};

        // 4. Continuously parse and merge subsequent sets.
        while(mExprIdx < mExprLen && mExpr[mExprIdx] == kComma) {
            ++mExprIdx;
            auto const term{parseConcatenation()};
            unionRes.insert(unionRes.end(), term.begin(), term.end());
        }

        return unionRes;
    }

    [[nodiscard]]
    auto parseConcatenation() -> std::vector<std::string> {
        // Provide an empty string identity element for Cartesian concatenation.
        auto concatenationRes{std::vector<std::string>{""s}};

        // 5. Build Cartesian products of contiguous sets until a delimiter.
        while(mExprIdx < mExprLen &&
            (std::islower(mExpr[mExprIdx]) || mExpr[mExprIdx] == kOpenBrace)
        ) {
            auto const factorRes{parseFactor()};
            // 6. Cross-multiply accumulated prefixes with newly parsed suffixes.
            auto concatPrefAndSuff{
                vs::cartesian_product(concatenationRes, factorRes) |
                vs::transform([] (auto const & prefStrAndSuffStr_) {
                    auto const & [prefStr, suffStr]{prefStrAndSuffStr_};
                    return prefStr + suffStr;
                })
            };

            concatenationRes = concatPrefAndSuff | rs::to<std::vector>();
        } 

        return concatenationRes;
    }

    [[nodiscard]]
    auto parseFactor() -> std::vector<std::string> {
        // 7. Handle nested sub-expressions enclosed in braces.
        if(mExpr[mExprIdx] == kOpenBrace) {
            ++mExprIdx;
            auto unionRes{ParseUnion()};
            ++mExprIdx;

            return unionRes;
        }

        // 8. Extract contiguous lowercase letters as a terminal leaf.
        auto const resFactor{
            mExpr |
            vs::drop(mExprIdx) |
            vs::take_while([] (auto const chr_) {return std::islower(chr_); }) |
            rs::to<std::string>()
        };
        mExprIdx += std::ssize(resFactor);

        return std::vector{resFactor};
    }

    std::string_view mExpr;
    ptrdiff_t mExprIdx{};
    ptrdiff_t mExprLen{};
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto braceExpansionII(
        std::string_view expression_
    ) ->  std::vector<std::string>;
};

auto Solution::braceExpansionII(
    std::string_view expression_
) ->  std::vector<std::string> {
    // Instantiate stateful parser for the given context.
    auto parser{Parser{expression_}};

    return parser.Parse();
}
