// problem : https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/description/
// submission : https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/submissions/1571265599
// solution post : https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/solutions/6528329/
//     c-modern-readable-code-beats-100-runtime-4sfk

// #include <queue>

// let 'l' be a length of the given matrix
// 'w' - width of the given matrix
// 'k' - count of weakest row indexes to select
// time complexity O(l + 3 * l * w + k * log(l)) -> O(l * w + k * log(l))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using MxT = std::vector<std::vector<int>>;
    using QelemT = MxT::value_type;
    std::vector<int> kWeakestRows(
        MxT & mx_,
        int k_
    ) const;
};

std::vector<int> Solution::kWeakestRows(
    MxT & mx_,
    int k_
) const {
    for(auto r{0}; r < mx_.size(); ++r) {
        mx_[r].emplace_back(r); 
    }
    auto pQ{std::priority_queue<QelemT, std::vector<QelemT>,
        std::greater<QelemT>>{std::greater<QelemT>{}, std::move(mx_)}};
    auto weakestKrowIdxs{std::vector<int>{}};
    weakestKrowIdxs.reserve(k_);
    for(; k_ > 0; --k_) {
        weakestKrowIdxs.emplace_back(pQ.top().back());
        pQ.pop();
    }
    return weakestKrowIdxs;
}
