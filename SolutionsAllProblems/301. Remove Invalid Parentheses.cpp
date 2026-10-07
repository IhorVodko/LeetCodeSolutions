// problem :       https://leetcode.com/problems/remove-invalid-parentheses/description
// submission :    https://leetcode.com/problems/remove-invalid-parentheses/submissions/2165295958
// solution post : https://leetcode.com/problems/remove-invalid-parentheses/solutions/8560933/
//                 simplanation-simple-explanation-by-cyber-r16y

// Approach : Depth-First Search with Parity Alternation
// Runtime :  0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the expression length
// Time :  O(2^n)
// Space : O(n^2)

// import std;

// #include <algorithm>
// #include <ios>
// #include <iostream>
// #include <ranges>
// #include <string>
// #include <utility>
// #include <vector>
// #include <cstddef>

namespace rs = std::ranges;
namespace vs = std::views;

namespace {

constexpr auto kOpenParen   {'('};
constexpr auto kCloseParen  {')'};

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
auto const fastIOInit
{
    []
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    }
    ()
};

struct VirtualParen final
{
    char openParen  {};
    char closeParen {};
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    auto removeInvalidParentheses(
            std::string expr_
    ) ->    std::vector<std::string>;

private:
    auto ConstructValidExprs(
            std::string             currExpr_,
            int             const   lastReadIdx_,
            int             const   lastRemoveIdx_,
            VirtualParen    const   virtParen_
    ) ->    void;

    std::vector<std::string> mValidExprs;
};

auto Solution::removeInvalidParentheses(
        std::string expr_
) ->    std::vector<std::string> 
{
    mValidExprs.clear();

    // 1. Initiate left-to-right pass to strip invalid closing parentheses.
    ConstructValidExprs(std::move(expr_), 0, 0, {kOpenParen, kCloseParen});

    return mValidExprs;
}

auto Solution::ConstructValidExprs(
        std::string             currExpr_,
        int             const   lastReadIdx_,
        int             const   lastRemoveIdx_,
        VirtualParen    const   virtParen_
) ->    void {
    auto const  [virtOpenParen, virtCloseParen]{virtParen_};
    auto        imbalanceCnt{0};

    // 2. Scan expression to locate the first structurally imbalanced parenthesis.
    for(auto const  [currReadIdx, currReadChr] :
            currExpr_ | vs::enumerate | vs::drop(lastReadIdx_)
    ) {
        if(currReadChr == virtOpenParen)
        {
            ++imbalanceCnt;
        }
        else if(currReadChr == virtCloseParen)
        {
            --imbalanceCnt;
        }

        if(imbalanceCnt >= 0) {
            continue;
        }

        // 3. Remove a single matching parenthesis from the imbalanced prefix.
        for(auto const currRemoveIdx: vs::iota(lastRemoveIdx_, currReadIdx + 1))
        {
            auto const isVirtCloseParen{currExpr_[currRemoveIdx] == virtCloseParen};
            // Deduplicate branches by pruning identical contiguous parentheses.
            auto const isDistinctParen{
                currRemoveIdx == lastRemoveIdx_ ||
                currExpr_[currRemoveIdx - 1] != virtCloseParen
            };

            if(isVirtCloseParen && isDistinctParen)
            {
                auto nextExpr{currExpr_};
                nextExpr.erase(currRemoveIdx, 1);

                // 4. Recurse down the search tree with the newly balanced prefix.
                ConstructValidExprs(std::move(nextExpr), currReadIdx, currRemoveIdx,
                                    virtParen_);
            }
        }

        // Halt branch exploration as current structural imbalance must be resolved.
        return;
    }

    // If globally balanced after Pass 1, save and exit early.
    if(imbalanceCnt == 0 && virtOpenParen == kOpenParen) {
        mValidExprs.emplace_back(std::move(currExpr_));
        return;
    }

    // 5. Flip string geometrically to reuse logic for inverse parenthesis targets.
    rs::reverse(currExpr_);

    if(virtOpenParen == kOpenParen)
    {
        // 6. Launch right-to-left verification for any remaining inverse invalid tokens.
        ConstructValidExprs(std::move(currExpr_), 0, 0, {kCloseParen, kOpenParen});
    }
    else
    {
        // 7. Store finalized valid string that survived bidirectional verification.
        mValidExprs.emplace_back(std::move(currExpr_));
    }
}
