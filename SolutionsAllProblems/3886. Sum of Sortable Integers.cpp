// problem : https://leetcode.com/problems/sum-of-sortable-integers/description
// submission : https://leetcode.com/problems/sum-of-sortable-integers/submissions/2177086510
// solution post : https://leetcode.com/problems/sum-of-sortable-integers/solutions/8581006/simplanation-simple-explanation-by-cyber-s1ng

// Approach : Divisor Chunking with O(1) Cyclic Validation
// Runtime : 16 ms, beats 92.65 %

// Complexity analysis
// let 'n' be the count of numbers
// Time :  O(n * sqrt(n))
// Space : O(n)

// import std;

// #include <algorithm>
// #include <ios>
// #include <iostream>
// #include <limits>
// #include <numeric>
// #include <ranges>
// #include <vector>

namespace rs = std::ranges;
namespace vs = std::views;

namespace {

constexpr auto kMaxDropCnt{1};

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
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
    auto sortableIntegers(std::vector<int> const & nums_) -> int;

private:
    [[nodiscard]]
    auto IsValidChunkSz(
        const int chunkSize_,
        std::vector<int> const & nums_
    ) -> bool;

    [[nodiscard]]
    auto CreatePrefixDropCnts(std::vector<int> const & nums_) -> std::vector<int>;

    [[nodiscard]]
    auto CreateNextDropIdxs(std::vector<int> const & nums_) -> std::vector<int>;

    std::vector<int> mPrefDropCnts;
    std::vector<int> mNextDropIdxs;

};

auto Solution::sortableIntegers(std::vector<int> const & nums_) -> int {
    const auto numsTot{static_cast<int>(nums_.size())};

    // 1. Handle base cases for minimal array sizes to avoid redundant computation and
    //  guard aginst out out of range index errors  
    if(numsTot == 1) {
        return 1;
    } else if(numsTot == 2) {
        return rs::is_sorted(nums_) ? 3 : 2;
    }

    // 2. Precompute prefix and next drop data for O(1) chunk property queries.
    mPrefDropCnts = CreatePrefixDropCnts(nums_);
    mNextDropIdxs = CreateNextDropIdxs(nums_);

    // 3. Generate valid divisors of the array size up to its square root.
    auto chunkSzSearchRng{
        vs::iota(1, numsTot + 1) |
        vs::take_while([numsTot] (auto const chunkSz_) {
            return chunkSz_ * chunkSz_ <= numsTot;
        }) |
        vs::filter([numsTot] (auto const chunkSz_) {
            return numsTot % chunkSz_ == 0;
        })
    };

    // 4. Accumulate valid chunk sizes including their co-divisors.
    auto const accumSum{[this, &nums_] (auto sum, auto const chunkSz_) {
        if(IsValidChunkSz(chunkSz_, nums_)) {
            sum += chunkSz_;
        }

        const auto pairedChunkSz{static_cast<int>(nums_.size()) / chunkSz_};
        if(pairedChunkSz != chunkSz_ && IsValidChunkSz(pairedChunkSz, nums_)) {
            sum += pairedChunkSz;
        }

        return sum;
    }};

    // 5. Fold over the search range to get the total sum of valid configurations.
    return rs::fold_left(chunkSzSearchRng, 0, accumSum);
}

auto Solution::IsValidChunkSz(
    const int chunkSize_,
    std::vector<int> const & nums_
) -> bool {
    const auto numsTot{static_cast<int>(nums_.size())};
    
    auto prevChunkMaxNum{std::numeric_limits<int>::min()};

    // Iterate over the array in strides matching the current chunk size.
    for(const auto startIdx: vs::iota(0, numsTot) | vs::stride(chunkSize_)) {
        const auto endIdx{startIdx + chunkSize_ - 1};
        auto chunkDropCnt{0};

        // Query the number of adjacent inversions within this specific chunk.
        if(endIdx > startIdx) {
            const auto beforeChunkDropCnt{
                startIdx > 0 ? mPrefDropCnts[startIdx - 1] : 0
            };

            chunkDropCnt = mPrefDropCnts[endIdx - 1] - beforeChunkDropCnt;
        }

        // A cyclically sortable chunk cannot have more than one inversion.
        if(chunkDropCnt > kMaxDropCnt) {
            return false;
        }

        auto currChunkMinNum{0};
        auto currChunkMaxNum{0};

        // Resolve chunk min and max boundaries when it is already perfectly sorted.
        if(chunkDropCnt == 0) {
            currChunkMinNum = nums_[startIdx];
            currChunkMaxNum = nums_[endIdx];

        // chunkDropCnt == kMaxDropCnt which is 1
        } else {
            // Ensure the cyclic shift remains strictly valid at the wrap-around point.
            if(nums_[endIdx] > nums_[startIdx]) {
                return false;
            }

            const auto dropIdx{mNextDropIdxs[startIdx]};

            currChunkMinNum = nums_[dropIdx + 1];
            currChunkMaxNum = nums_[dropIdx];
        }

        // Verify that the chunks maintain global sorted order relative to each other.
        if(prevChunkMaxNum > currChunkMinNum) {
            return false;
        }

        prevChunkMaxNum = currChunkMaxNum;
    }

    return true;
}

auto Solution::CreatePrefixDropCnts(std::vector<int> const & nums_) -> std::vector<int> {
    const auto numsTot{static_cast<int>(nums_.size())};
    auto prefDropCnts{std::vector<int>(numsTot)};

    // Flag every index where the element is greater than its immediate successor.
    const auto adjDropsView{
        nums_ |
        vs::adjacent_transform<2>([](const auto currNum_, const auto nextNum_) {
            return currNum_ > nextNum_ ? 1 : 0;
        })
    };

    // Transform flags into a prefix sum array to enable range counting.
    std::inclusive_scan(
        adjDropsView.begin(),
        adjDropsView.end(),
        prefDropCnts.begin()
    );

    prefDropCnts.back() = prefDropCnts[numsTot - 2];

    return prefDropCnts;
}

auto Solution::CreateNextDropIdxs(std::vector<int> const & nums_) -> std::vector<int> {
    const auto numsTot{static_cast<int>(nums_.size())};
    auto nextDropIdxs{std::vector<int>(numsTot)};

    // Map each index to the nearest rightward inversion by reverse traversal.
    const auto revDropIdxsView{
        vs::iota(0, numsTot - 1) 
        | vs::reverse 
        | vs::transform([&nums_, numsTot](const auto idx_) {
            return nums_[idx_] > nums_[idx_ + 1] ? idx_ : numsTot;
        })
    };

    // Scan iteratively backwards to persist the index of the next occurring drop.
    std::inclusive_scan(
        revDropIdxsView.begin(),
        revDropIdxsView.end(),
        nextDropIdxs.rbegin() + 1,
        [](const auto currIdx_, const auto nextIdx_) {
            return std::min(currIdx_, nextIdx_);
        }
    );

    return nextDropIdxs;
}
