// problem : https://leetcode.com/problems/count-good-triplets-in-an-array/description/
// submission : https://leetcode.com/problems/count-good-triplets-in-an-array/submissions/1608414271
// solution post : https://leetcode.com/problems/count-good-triplets-in-an-array/solutions/6656216/
//     c-modern-readable-code-optimal-time-comp-sf6n

// #include <vector>

// let 'n' be a count of given numbers
// time complexity O(n * log(n))
// space complexity O(n)
// runtime 19 ms, beats 87.28 %
namespace Utility {

class FenwickTree {
public:
    void Update(
        int index_,
        int const delta_
    ) {
        ++index_;
        while(index_ < mTree.size()) {
            mTree[index_] += delta_;
            index_ += index_ & -index_;
        }
    }
    int Query(int index_) {
        ++index_;
        auto result{0};
        while(index_ > 0) {
            result += mTree.at(index_);
            index_ -= index_ & -index_;
        }
        return result;
    }
    explicit FenwickTree(size_t const size_):
        mTree(size_ + 1, 0)
    {}
private:
    std::vector<int> mTree;
};

}

class Solution {
public:
    long long goodTriplets(
        std::vector<int> const & nums1_,
        std::vector<int> const & nums2_
    ) const {
        using namespace Utility;
        auto const nums1Count{nums1_.size()};
        auto pos2{std::vector<int>(nums1Count, -1)};
        auto reveresedIndexMapping{std::vector<int>(nums1Count, -1)};
        for(auto i{0}; i < nums1Count; ++i) {
            pos2.at(nums2_.at(i)) = i;
        }
        for(auto i{0}; i < nums1Count; ++i) {
            reveresedIndexMapping.at(pos2.at(nums1_[i])) = i;
        }
        auto tree{FenwickTree{nums1Count}};
        auto result{0LL};
        for(auto num{0}; num < nums1Count; ++num) {
            auto const pos{reveresedIndexMapping[num]};
            auto left{tree.Query(pos)};
            tree.Update(pos, 1);
            auto right{(nums1Count - 1 - pos) - (num - left)};
            result += static_cast<long long>(left) * right;
        }
        return result;
    }
};
