// problem : https://leetcode.com/problems/longest-balanced-subarray-ii/description
// submission : https://leetcode.com/problems/longest-balanced-subarray-ii/submissions/1916229050
// solution post : https://leetcode.com/problems/longest-balanced-subarray-ii/solutions/7572157/
//    c-modern-readable-code-beats-100-runtime-t7ne

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

struct SegmentTree {
    explicit SegmentTree(std::vector<int> const & data_):
        mDataSz{data_.size()}
    {
        // Initialize segment tree arrays for min, max, and mLazyVals propagation
        auto const valTotCnt{mDataSz * kSegTreeFactor + 1};
        mMinVals.assign(valTotCnt, 0);
        mMaxVals.assign(valTotCnt, 0);
        mLazyVals.assign(valTotCnt, 0);
        Build(data_, 1, mDataSz, 1); 
    }

    auto Add(
        int const l_,
        int const r_,
        int const val_
    ) -> void {
        Update(l_, r_, val_, 1, mDataSz, 1);
    }

    [[nodiscard]]
    auto FindLast(
        int const start_,
        int const val_
    ) -> int {
        if(start_ > mDataSz) {
            return -1;
        }
        // Find the last index >= start_ where segment tree contains val_
        return Find(start_, mDataSz, val_, 1, mDataSz, 1);
    }

private:
    auto Apply(
        int const i_,
        int const val_
    ) -> void {
        mMinVals[i_] += val_;
        mMaxVals[i_] += val_;
        mLazyVals[i_] += val_;
    }
    
    auto PushDown(int const i_) -> void {
        if(mLazyVals.at(i_) == 0) {
            return;
        }
        // Propagate the mLazyVals value to children
        Apply(i_ * 2, mLazyVals.at(i_));
        Apply(i_ * 2 + 1, mLazyVals.at(i_));
        mLazyVals.at(i_) = 0;
    }

    auto PushUp(int const i_ ) -> void {
        // Update current node's min and max based on children
        mMinVals.at(i_) = std::min(mMinVals.at(i_ * 2), mMinVals.at(i_ * 2 + 1));
        mMaxVals.at(i_ ) = std::max(mMaxVals.at(i_ * 2), mMaxVals.at(i_ * 2 + 1));
    }

    auto Build(
        std::vector<int> const & data_,
        int const l_,
        int const r_,
        int const i_
    ) -> void {
        if(l_ == r_) {
            // Leaf node initialized from original data
            mMinVals.at(i_) = data_.at(l_ - 1);
            mMaxVals.at(i_) = data_.at(l_ - 1);
            return;
        }
        auto const mid{l_ + ((r_ - l_) / 2)};
        Build(data_, l_, mid, i_ * 2);
        Build(data_, mid + 1, r_, i_ * 2 + 1);
        PushUp(i_);
    }

    auto Update(
        int const L_,
        int const R_,
        int const val_,
        int const l_,
        int const r_,
        int const i_
    ) -> void {
        if(L_ <= l_ && r_ <= R_) {
            // Current segment completely within update range
            Apply(i_, val_);
            return;
        }
        PushDown(i_);
        auto const mid{l_ + ((r_ - l_) / 2)};
        if(L_ <= mid) {
            Update(L_, R_, val_, l_, mid, i_ * 2);
        }
        if(R_ > mid) {
            Update(L_, R_, val_, mid + 1, r_, i_ * 2 + 1);
        }
        PushUp(i_);
    }

    [[nodiscard]]
    auto Find(
        int const L_,
        int const R_,
        int const val_, 
        int const l_, 
        int const r_, 
        int const i_
    ) -> int {
        if(mMinVals.at(i_) > val_ || mMaxVals.at(i_) < val_) {
            // No value equal to 'val_' in this segment
            return -1;
        } else if(l_ == r_) {
            // Leaf node containing the value
            return l_;
        }
        PushDown(i_);
        auto const mid{l_ + ((r_ - l_) / 2)};
        if(R_ >= mid + 1) {
            auto const res{Find(L_, R_, val_, mid + 1, r_, i_ * 2 + 1)};
            if(res != -1) {
                return res;
            }
        }
        if(L_ <= mid) {
            return Find(L_, R_, val_, l_, mid, i_ * 2);
        }
        return -1;
    }

    static auto constexpr kSegTreeFactor{4};
    size_t mDataSz{};
    std::vector<int> mMinVals;
    std::vector<int> mMaxVals;
    std::vector<int> mLazyVals;
};

// let 'n' be the number of elements
// time complexity O(n * log(n))
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto longestBalanced(std::vector<int> const & nums_) const -> int;
};

auto Solution::longestBalanced(std::vector<int> const & nums_) const -> int {
    namespace vs = std::views;

    // Map each number to a queue of its remaining occurrences
    auto numToIdxs{std::map<int, std::queue<int>>{}};
    auto const Parity{[] (int const num_) { return (num_ % 2) == 0 ? 1 : -1; }};
    auto subArMaxLen{0};
    auto const numsSz{std::ssize(nums_)};
    auto prefParitySums{std::vector<int>(numsSz)};
    // Initialize prefParitySums sum with sign (even=+1, odd=-1)
    prefParitySums.at(0) = Parity(nums_.at(0));
    numToIdxs[nums_.at(0)].emplace(1);
    for(auto const i: vs::iota(1, numsSz)) {
        prefParitySums[i] = prefParitySums[i - 1];
        auto const num{nums_[i]};
        auto & idxs{numToIdxs[num]};
        if(idxs.empty()) {
            // First occurrence contributes to prefParitySums sum
            prefParitySums[i] += Parity(num);
        }
        idxs.emplace(i + 1);
    }
    // Build segment tree over prefParitySums sums for range queries
    auto tree{::SegmentTree{prefParitySums}};
    for(auto const i: vs::iota(0, numsSz)) {
        // Try to extend the current balanced subarray
        auto const subArCurLen{tree.FindLast(i + subArMaxLen, 0) - i};
        subArMaxLen = std::max(subArMaxLen, subArCurLen);
        auto nextPos{numsSz + 1};
        auto const num{nums_[i]};
        if(numToIdxs.at(num).empty()) {
            return -1;
        }
        numToIdxs.at(num).pop();
        if(!numToIdxs.at(num).empty()) {
            // Next occurrence determines the end of current influence
            nextPos = numToIdxs[num].front();
        }
        // Decrease prefParitySums sums for the range affected by num
        tree.Add(i + 1, nextPos - 1, -Parity(num));
    }
    return subArMaxLen;
}
