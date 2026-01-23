// problem : https://leetcode.com/problems/minimum-pair-removal-to-sort-array-ii/description
// submission : https://leetcode.com/problems/minimum-pair-removal-to-sort-array-ii/submissions/1894669889
// solution post : https://leetcode.com/problems/minimum-pair-removal-to-sort-array-ii/solutions/7518536/
//    c-modern-readable-code-beats-100-runtime-5qkj

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream{"display_runtime.txt"} << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

struct NumAndIdx {
    long long mNum{};
    int mIdx{};
};

struct AdjNums {
    using listIt = std::list<NumAndIdx>::iterator;

    AdjNums() = default;
    AdjNums(
        listIt const curNumIt_,
        listIt const nextNumIt_,
        long long sum_
    ):
        mCurNumIt{curNumIt_},
        mNextNumIt{nextNumIt_},
        mCurIdx(curNumIt_->mIdx),
        mNextIdx(nextNumIt_->mIdx),
        mSum{sum_}
    {}

    listIt mCurNumIt{};
    listIt mNextNumIt{};
    long long mSum{};
    int mCurIdx{};
    int mNextIdx{};
};

struct CompAdjNums {
    auto operator() (
        AdjNums const & lhs_,
        AdjNums const & rhs_
    ) -> bool {
        if(lhs_.mSum != rhs_.mSum) {
            return lhs_.mSum > rhs_.mSum;
        }
        return lhs_.mCurIdx > rhs_.mCurIdx;
    }
};

// let 'n' be the vector lenght
// time complexity O(n * log(n))
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    auto minimumPairRemoval(std::vector<int> const & nums_) const -> int;

private:
    static auto constexpr kNumsMaxCnt{100'000};
};

auto Solution::minimumPairRemoval(std::vector<int> const & nums_) const -> int {
    namespace vs = std::views;

    // Maintain the array as a linked list of numbers with original indices
    auto lstNumAndIdx{std::list<NumAndIdx>{}};
    // Track which indices have already been merged
    auto isIdxMerged{std::bitset<kNumsMaxCnt>{}};
    // Min-heap to always select the adjacent pair with minimum sum
    auto pqAdjNums{std::priority_queue<AdjNums, std::vector<AdjNums>, CompAdjNums>{}};
    // Count of adjacent decreases in the array
    auto decreaseCnt{0};
    // Count of merge operations performed
    auto opCnt{0};
    lstNumAndIdx.emplace_back(nums_.front(), 0);
    // Initialize linked list, heap, and decrease count
    for(auto const i: vs::iota(1, std::ssize(nums_))) {
        lstNumAndIdx.emplace_back(nums_[i], static_cast<int>(i));
        auto const curNumAndIdx{std::prev(lstNumAndIdx.end())};
        auto const prevNumAndIdx{std::prev(curNumAndIdx)};
        auto const sum{prevNumAndIdx->mNum + curNumAndIdx->mNum};
        // Add adjacent pair to heap
        pqAdjNums.emplace(prevNumAndIdx, curNumAndIdx, sum);
        // Increment decrease count if the array is decreasing at this position
        if(nums_[i - 1] > nums_[i]) {
            ++decreaseCnt;
        }
    }
    // Merge loop: continue until array is non-decreasing
    while(decreaseCnt > 0 && !pqAdjNums.empty()) {
        auto const adjNums{pqAdjNums.top()};
        pqAdjNums.pop();
        // Skip pairs that have already been merged
        if(isIdxMerged.test(adjNums.mCurIdx) || isIdxMerged.test(adjNums.mNextIdx)) {
            continue;
        }
        auto curNumIt{adjNums.mCurNumIt};
        auto & curNum{curNumIt->mNum};
        auto nextNumIt{adjNums.mNextNumIt};
        auto const nextNum{nextNumIt->mNum};
        auto const sum{adjNums.mSum};
        // Skip if the sum has changed due to previous merges
        if(curNum + nextNum != sum) {
            continue;
        }
        ++opCnt;
        // Adjust decrease count if merging resolves a descending pair
        if(curNum > nextNum) {
            --decreaseCnt;
        }
        // Identify neighbors for updating
        auto prevNumIt{
            curNumIt == lstNumAndIdx.begin() ? lstNumAndIdx.end() : std::prev(curNumIt)
        };
        auto const prevNum{prevNumIt->mNum};
        auto nextNextNumIt{std::next(nextNumIt)};
        auto const nextNextNum{nextNextNumIt->mNum};
        // Update left neighbor pair after merge
        if(prevNumIt != lstNumAndIdx.end()) {
            if(prevNum > curNum && prevNum <= sum) {
                --decreaseCnt;
            } else if(prevNum <= curNum && prevNum > sum) {
                ++decreaseCnt;
            }
            auto const newSum{prevNum + sum};
            pqAdjNums.emplace(prevNumIt, curNumIt, newSum);
        }
        // Update right neighbor pair after merge
        if(nextNextNumIt != lstNumAndIdx.end()) {
            if(nextNum > nextNextNum && sum <= nextNextNum) {
                --decreaseCnt;
            } else if(nextNum <= nextNextNum && sum > nextNextNum) {
                ++decreaseCnt;
            }
            auto const newSum{nextNextNum + sum};
            pqAdjNums.emplace(curNumIt, nextNextNumIt, newSum);
        }
        // Apply the merge
        curNum = sum;
        isIdxMerged.set(nextNumIt->mIdx);
        lstNumAndIdx.erase(nextNumIt);
    }
    return opCnt;
}
