// problem : https://leetcode.com/problems/maximize-active-section-with-trade-ii/description
// submission : https://leetcode.com/problems/maximize-active-section-with-trade-ii/submissions/2077340958
// solution post : https://leetcode.com/problems/maximize-active-section-with-trade-ii/solutions/8413457/
//    modern-readable-code-optimal-time-comple-rcel

// Approach : Sparse Table with Range Maximum Queries (RMQ) for Contiguous Segment Merging
// Runtime : 41 ms, beats 93.55 %

// Complexity analysis
// let 'n' be the total number of sections given
// 'k' - number of inactive groups (k <= n / 2)
// 'q' - number of queries
// Time :  O(n * log(n) + q)
// Space : O(n * log(n))

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

using vec2d = std::vector<std::vector<int>>;

auto constexpr kZero{'0'};
auto constexpr kOne{'1'};

struct ZeroGrp {
    int startIdx{};
    int len{};
};

// Initialize fast I/O operations
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
    static auto maxActiveSectionsAfterTrade(
        std::string_view const sections_,
        vec2d const & queries_
    ) -> std::vector<int>;
};

auto Solution::maxActiveSectionsAfterTrade(
    std::string_view const sections_,
    vec2d const & queries_
) -> std::vector<int> {
    auto const totSections{static_cast<int>(sections_.size())};
    auto totOnes{0};
    auto zeroGrps{std::vector<ZeroGrp>{}};
    auto lastZeroGrpId{std::vector<int>(totSections, -1)};

    // Chunk the string by contiguous identical characters
    for(auto idx{0}, grpID{-1};
        auto const section : sections_ | vs::chunk_by(std::equal_to{})
    ) {
        auto const sectionLen{static_cast<int>(rs::distance(section))};

        // Record contiguous groups of zeros
        if(section.front() == kZero) {
            ++grpID;
            zeroGrps.emplace_back(idx, sectionLen);
        } else {
            totOnes += static_cast<int>(rs::distance(section));
        }

        // Map every index to the most recently encountered zero-group ID
        for(auto const sectionIdx: vs::iota(idx, idx + sectionLen)) {
            lastZeroGrpId[sectionIdx] = grpID;
        }

        idx += sectionLen;
    }

    // No inactive sections available to trade
    if(zeroGrps.empty()) {
        return std::vector(queries_.size(), totOnes);
    }

    auto const totAdjPairs{std::max(0, static_cast<int>(zeroGrps.size()) - 1)};
    auto const maxLog2Step{
        static_cast<int>(std::bit_width(static_cast<unsigned>(totAdjPairs)))
    };
    // A sparse table for O(1) Range Maximum Queries on adjacent zero-groups
    auto sparseTbl{std::vector<int>(std::max(1, maxLog2Step) * totAdjPairs)};

    auto const CalcTblIdx{
        [=](int const logStep_, int const pairIdx_) -> int { 
            return logStep_ * totAdjPairs + pairIdx_; 
        }
    };

    // Construct a sparse table
    if(totAdjPairs > 0) {
        for(auto const pairIdx: vs::iota(0, totAdjPairs)) {
            sparseTbl[CalcTblIdx(0, pairIdx)] =
                zeroGrps[pairIdx].len + zeroGrps[pairIdx + 1].len;
        }

        for(auto const logStep: vs::iota(1, maxLog2Step)) {
            for(auto pairIdx{0}; pairIdx + (1 << logStep) <= totAdjPairs; ++pairIdx) {
                sparseTbl[CalcTblIdx(logStep, pairIdx)] = std::max(
                    sparseTbl[CalcTblIdx(logStep - 1, pairIdx)],
                    sparseTbl[CalcTblIdx(logStep - 1, pairIdx + (1 << (logStep - 1)))]
                );
            }
        }
    }

    // Retrieve maximum sum of fully enclosed adjacent zero-groups using the sparse table
    auto const CalcMaxAdjSum{[&] (int const leftIdx_, int const rightIdx_) -> int {
        if(leftIdx_ > rightIdx_) return 0;

        auto const rngLen{static_cast<unsigned>(rightIdx_ - leftIdx_ + 1)};
        auto const logStep{static_cast<int>(std::bit_width(rngLen)) - 1};

        return std::max(
            sparseTbl[CalcTblIdx(logStep, leftIdx_)], 
            sparseTbl[CalcTblIdx(logStep, rightIdx_ - (1 << logStep) + 1)]
        );
    }};

    auto const SolveQuery{[&] (std::vector<int> const & query_) -> int {
        auto const qrStart_{query_[0]};
        auto const qrEnd_{query_[1]};

        auto const leftGrpId{lastZeroGrpId[qrStart_]};
        auto const rightGrpId{lastZeroGrpId[qrEnd_]};

        auto const firstFullyEnclosedGrpId{leftGrpId + 1};
        auto const lastFullyEnclosedGrpId{
            rightGrpId - (sections_[qrEnd_] == kZero ? 1 : 0)
        };

        // Calculate available lengths for zero-groups truncated by query boundaries
        auto const firstPartialGrpId{leftGrpId == -1 ?
            -1 :
            (zeroGrps[leftGrpId].len - (qrStart_ - zeroGrps[leftGrpId].startIdx))   
        };
        auto const lastPartialGrpId{rightGrpId == -1 ?
            -1 :
            (qrEnd_ - zeroGrps[rightGrpId].startIdx + 1)
        };

        auto maxTotMergedZeros{0};

        // Case 1: Max sum from pairs entirely inside the query range
        if(firstFullyEnclosedGrpId < lastFullyEnclosedGrpId) {
            maxTotMergedZeros = std::max(
                maxTotMergedZeros, 
                CalcMaxAdjSum(firstFullyEnclosedGrpId, lastFullyEnclosedGrpId - 1)
            );
        } 
        // Case 2: Query boundaries truncate two distinct adjacent zero-groups
        if( sections_[qrStart_] == kZero &&
            sections_[qrEnd_] == kZero &&
            leftGrpId + 1 == rightGrpId
        ) {
            maxTotMergedZeros = std::max(
                maxTotMergedZeros, 
                firstPartialGrpId + lastPartialGrpId
            );
        } 
        // Case 3: Left boundary truncates a group, adjacent group is fully enclosed
        if( sections_[qrStart_] == kZero && 
            leftGrpId + 1 < rightGrpId + (sections_[qrEnd_] == kOne ? 1 : 0)
        ) {
            maxTotMergedZeros = std::max(
                maxTotMergedZeros, 
                firstPartialGrpId + zeroGrps[leftGrpId + 1].len
            );
        } 
        // Case 4: Right boundary truncates a group, prior group is fully enclosed
        if( sections_[qrEnd_] == kZero && 
            leftGrpId < rightGrpId - 1
        ) {
            maxTotMergedZeros = std::max(
                maxTotMergedZeros, 
                lastPartialGrpId + zeroGrps[rightGrpId - 1].len
            );
        }

        return totOnes + maxTotMergedZeros;
    }};

    // Process all queries and materialize results into a vector
    return
        queries_ |
        vs::transform([&] (auto const & queryRange) { return SolveQuery(queryRange); }) |
        rs::to<std::vector<int>>()
    ;
}
