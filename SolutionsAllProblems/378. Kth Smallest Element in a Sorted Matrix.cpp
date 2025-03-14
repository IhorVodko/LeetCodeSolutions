// problem : https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/description/
// submission : https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/submissions/1573913242
// solution post : https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/solutions/6537258/
//     c-modern-readable-code-by-cyberartist-4yp4

// #include <algorithm>
// #include <queue>
// #include <vector>

// let 'a' be a length of the given array
// 'k' - the kTh count of the required smallest num
// time complexity O(min(a, k) + k * log(min(a, k))
// space complexity O(min(a, k))
// runtime 11 ms, beats 28.66 %
class Solution {
public:
    using MxT = std::vector<std::vector<int>>;
    using QueueT = std::array<int, 3>;
    int kthSmallest(
        MxT const & mx_,
        int const kthSmallest
    ) const;
};

int Solution::kthSmallest(
    MxT const & mx_,
    int const kThSmallest
) const {
    auto kSmallestNums{std::priority_queue<QueueT, std::vector<QueueT>,
        std::greater<QueueT>>{}};
    auto const mxSz{mx_.size()};
    auto const qSz{std::min(mxSz, static_cast<size_t>(kThSmallest))};
    for(auto r{0}; r < qSz; ++r) {
        kSmallestNums.emplace(QueueT{mx_[r][0], r, 0});
    } 
    for(auto numTh{1}; numTh < kThSmallest; ++numTh) {
        auto const [num, r, c]{kSmallestNums.top()};
        kSmallestNums.pop();
        if(c < mxSz - 1) {
            kSmallestNums.emplace(QueueT{mx_[r][c + 1], r, c + 1});
        }
    }
    return kSmallestNums.top()[0];
}
