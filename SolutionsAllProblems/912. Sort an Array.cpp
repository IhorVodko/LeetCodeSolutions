// problem : https://leetcode.com/problems/sort-an-array/description
// submission : https://leetcode.com/problems/sort-an-array/submissions/1687482471
// solution post : https://leetcode.com/problems/sort-an-array/solutions/6924347/
//    c-modern-readable-code-optimal-time-comp-xvmk

// #include <iterator>
// #include <ranges>
// #include <span>
// #include <vector>

class Solution {
public:
// let 'n' be a count of the given numbers
// time complexity O(n * log2(n))
// space complexity O(n)
// runtime 83 ms, beats 64.03 %
    std::vector<int> sortArray(std::vector<int> & nums_);
private:
    void DoMergeSort(
        std::span<int> nums_,
        int const idxFirst_,
        int const idxLast_
    );
    void Merge(
        std::span<int> nums_,
        int const idxFirst_,
        int const idxMid_,
        int const idxLast_
    );
    std::vector<int> mNumsTemp;
};

std::vector<int> Solution::sortArray(std::vector<int> & nums_) {
    auto const numsSz{std::ssize(nums_)};
    mNumsTemp = std::vector<int>(numsSz, 0);
    DoMergeSort(nums_, 0, numsSz - 1);
    return nums_;
}

void Solution::DoMergeSort(
    std::span<int> nums_,
    int const idxFirst_,
    int const idxLast_
) {
    if(idxFirst_ >= idxLast_) {
        return;
    }
    auto const idxMid{idxFirst_ + ((idxLast_ - idxFirst_) / 2)};
    DoMergeSort(nums_, idxFirst_, idxMid);
    DoMergeSort(nums_, idxMid + 1, idxLast_);
    Merge(nums_, idxFirst_, idxMid, idxLast_);
}

void Solution::Merge(
    std::span<int> nums_,
    int const idxFirst_,
    int const idxMid_,
    int const idxLast_
) {
    namespace ranges = std::ranges;
    auto const numsLeftSz{idxMid_ - idxFirst_ + 1};
    auto const numsRightSz{idxLast_ - idxMid_};
    auto const numsTempBeg{mNumsTemp.begin()};
    ranges::copy(nums_.subspan(idxFirst_, numsLeftSz),
        numsTempBeg + idxFirst_);
    ranges::copy(nums_.subspan(idxMid_ + 1, numsRightSz),
        numsTempBeg + idxMid_ + 1);
    auto idxOffsetIn1{0};
    auto idxOffsetIn2{0};
    auto idxOut{idxFirst_};
    auto const idxFirst2{idxMid_ + 1};
    while(idxOffsetIn1 < numsLeftSz && idxOffsetIn2 < numsRightSz) {
        auto const idxIn1{idxFirst_ + idxOffsetIn1};
        auto const idxIn2{idxFirst2 + idxOffsetIn2};
        if(mNumsTemp.at(idxIn1) <= mNumsTemp.at(idxIn2)) {
            nums_[idxOut] = mNumsTemp.at(idxIn1);
            ++idxOffsetIn1;
        } else {
            nums_[idxOut] = mNumsTemp.at(idxIn2);
            ++idxOffsetIn2;
        }
        ++idxOut;
    }
    while(idxOffsetIn1 < numsLeftSz) {
        nums_[idxOut++] = mNumsTemp.at(idxFirst_ + idxOffsetIn1++);
    }
    while(idxOffsetIn2 < numsRightSz) {
        nums_[idxOut++] = mNumsTemp.at(idxFirst2 + idxOffsetIn2++);
    }
}
