// problem : https://leetcode.com/problems/k-closest-points-to-origin/description/
// submission : https://leetcode.com/problems/k-closest-points-to-origin/submissions/1579031477
// solution post : https://leetcode.com/problems/k-closest-points-to-origin/solutions/6555544/
//     c-modern-readable-code-beats-96-runtime-qyti3

// #include <algorithm>
// #include <functional>
// #include <queue>
// #include <vector>

// let 'p' be cont of points given
// 'd' - the count of smallest distances to select
// time complexity O(n * log2(d))
// space complexity O(d)
// runtime 18 ms, beats 96.09 %
class Solution {
public:
    using PointT = std::vector<int>;
    std::vector<PointT> kClosest(
        std::vector<PointT> const & points_,
        int const k_
    ) {
        mPointIdx = 0;
        mK = k_;    
        std::for_each(points_.begin(), points_.end(), mDistanceManager);
        auto closestKPoints{std::vector<PointT>{}};
        while(!mClosestKPoints.empty()) {
            closestKPoints.emplace_back(points_.at(mClosestKPoints.top().second));
            mClosestKPoints.pop();
        }
        return closestKPoints;
    }
    Solution():
        mPointIdx{0},
        mK{0}
    {}
private:
    std::function<void(PointT const &)> mDistanceManager{
        [&] (PointT const & point_) {
            auto distance{std::pow(point_.front(), 2) +
                std::pow(point_.back(), 2)};
            if(mClosestKPoints.size() < mK) {
                mClosestKPoints.emplace(distance, mPointIdx);
            } else {
                if(mClosestKPoints.top().first > distance) {
                    mClosestKPoints.pop();
                    mClosestKPoints.emplace(distance, mPointIdx);
                }
            } 
            ++mPointIdx;
        } 
    };
    size_t mPointIdx;
    int mK;
    std::priority_queue<std::pair<double, size_t>,
        std::vector<std::pair<double, size_t>>,
        std::less<std::pair<double, size_t>>>
    mClosestKPoints;
};
