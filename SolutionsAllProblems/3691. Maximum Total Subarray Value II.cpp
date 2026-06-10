// problem : https://leetcode.com/problems/maximum-total-subarray-value-ii/description
// submission : https://leetcode.com/problems/maximum-total-subarray-value-ii/submissions/2028933492
// solution post : https://leetcode.com/problems/maximum-total-subarray-value-ii/solutions/8326431/
//    c-modern-readable-code-beats-100-runtime-hfhx

// Approach : Greedy Range Shrinking via Max-Heap and RMQ
// Runtime : 57 ms, beats 100.00 %

// Complexity
// let 'n' be the count of numbers
// 'm' - the reuqired number of sub-arrays
// Time :  O(log(n) * (n + m))
// Space : O(n * log(n))

struct SubArrData {
    // Prioritize larger differences in the max-heap
    [[nodiscard]]
    constexpr auto operator<(SubArrData const & other_) const noexcept -> bool {
        return mMinMaxDiff < other_.mMinMaxDiff;
    }

    int mBegIdx{};
    int mEndIdx{};
    int mMinMaxDiff{};
};

class SparseTable {
public:
    // Precompute lookup tables for RMQ using dynamic programming
    explicit SparseTable(std::span<const int> const nums_) {
        namespace rs = std::ranges;
        namespace vs = std::views;

        auto const numsSz{static_cast<int>(nums_.size())};
        auto const bitW{std::bit_width(static_cast<unsigned>(numsSz))};

        mMins.assign(bitW, std::vector<int>(numsSz));
        mMaxs.assign(bitW, std::vector<int>(numsSz));

        rs::copy(nums_, mMins[0].begin());
        rs::copy(nums_, mMaxs[0].begin());

        for(auto const bitIdx: vs::iota(1, bitW)) {
            for(auto const numIdx: vs::iota(0, numsSz - (1 << bitIdx) + 1)) {
                mMins[bitIdx][numIdx] = std::min(
                    mMins[bitIdx - 1][numIdx],
                    mMins[bitIdx - 1][numIdx + (1 << (bitIdx - 1))]
                );
                mMaxs[bitIdx][numIdx] = std::max(
                    mMaxs[bitIdx - 1][numIdx],
                    mMaxs[bitIdx - 1][numIdx + (1 << (bitIdx - 1))]
                );
            }
        }
    }

    // Resolves range minimum queries in O(1) time
    [[nodiscard]]
    auto CalcMin(
        int const lIdx_, 
        int const rIdx_
    ) const noexcept -> int {
        auto const bitIdx{std::bit_width(static_cast<unsigned>(rIdx_ - lIdx_ + 1)) - 1};
        return std::min(mMins[bitIdx][lIdx_], mMins[bitIdx][rIdx_ - (1 << bitIdx) + 1]);
    }

    // Resolves range maximum queries in O(1) time
    [[nodiscard]]
    auto GetMax(
        int const lIdx_,
        int const rIdx_
    ) const noexcept -> int {
        auto const bitIdx{std::bit_width(static_cast<unsigned>(rIdx_ - lIdx_ + 1)) - 1};
        return std::max(mMaxs[bitIdx][lIdx_], mMaxs[bitIdx][rIdx_ - (1 << bitIdx) + 1]);
    }

private:
    std::vector<std::vector<int>> mMins;
    std::vector<std::vector<int>> mMaxs;
};

class Solution final {
public:
    using ll = long long;

    [[nodiscard]]
    static auto maxTotalValue(
        std::vector<int> & nums_,
        int const subArrTot_
    ) -> ll;
};

auto Solution::maxTotalValue(
    std::vector<int> & nums_,
    int const subArrTot_
) -> ll {
    namespace rs = std::ranges;
    namespace vs = std::views;

    auto const numsSz{static_cast<int>(nums_.size())};
        
    // Handle trivial array lengths
    if(numsSz == 1) {
        return 0;
    }
    if(numsSz == 2) {
        auto const [minVal, maxVal]{rs::minmax(nums_)};
        return static_cast<ll>(maxVal - minVal);
    }

    // Precalculate suffix extremums to identify optimal bounds globally
    auto suffixExtremums{std::vector<std::pair<int, int>>(
        numsSz, {nums_.back(), nums_.back()}
    )};
    for(auto const j: vs::iota(0, numsSz - 1) | vs::reverse) {
        auto & [currMinVal, currMaxVal]{suffixExtremums[j]};
        auto const num{nums_[j]};
        auto const [nextMinVal, nextMaxVal]{suffixExtremums[j + 1]};
        currMinVal = std::min(num, nextMinVal);
        currMaxVal = std::max(num, nextMaxVal);
    }

    auto const globalDiff{static_cast<ll>(
        suffixExtremums.front().second - suffixExtremums.front().first
    )};
    // Edge case
    if(globalDiff == 0) {
        return 0;
    }

    auto subArrCnt{0};
    auto minIdx{-1uz};
    auto maxIdx{-1uz};

    // Evaluate occurrences that yield the maximum possible difference
    for(auto const [j, num] : nums_ | vs::enumerate) {
        auto const [minVal, maxVal]{suffixExtremums.front()};
        if(num == minVal) {
            minIdx = j;
        }
        if(num == maxVal) {
            maxIdx = j;
        }
        if(minIdx != -1 && maxIdx != -1) {
            subArrCnt += std::min(minIdx, maxIdx) + 1;
        }
    }

    // Fast-path execution if the quota can be met purely with global maximums
    if(subArrCnt >= subArrTot_) {
        return globalDiff * subArrTot_;
    }

    // Fallback logic for complex cases
    auto const table{SparseTable{nums_}};
    auto pq{std::priority_queue<SubArrData>{}};

    // Seed the queue with the largest possible suffix lengths
    for(auto const lIdx : vs::iota(0, numsSz)) {
        auto const maxVal{table.GetMax(lIdx, numsSz - 1)};
        auto const minVal{table.CalcMin(lIdx, numsSz - 1)};
        pq.emplace(lIdx, numsSz - 1, maxVal - minVal);
    }

    auto totVal{0ll};

    // Systematically extract the optimal selections and append narrowed branches
    for(auto const subArrCnt : vs::iota(0, subArrTot_)) {
        if(pq.empty()) {
            break;
        } 

        auto const [begIdx, endIdx, diff]{pq.top()};
        pq.pop();

        totVal += diff;
        
        if(begIdx < endIdx && subArrCnt < subArrTot_ - 1) {
            auto const maxVal{table.GetMax(begIdx, endIdx - 1)};
            auto const minVal{table.CalcMin(begIdx, endIdx - 1)};
            pq.emplace(begIdx, endIdx - 1, maxVal - minVal);
        }
    }

    return totVal;
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
