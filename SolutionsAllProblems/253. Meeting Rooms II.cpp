// problem : https://leetcode.com/problems/meeting-rooms-ii/description/
// submission : https://leetcode.com/problems/meeting-rooms-ii/submissions/1578979330
// solution post : https://leetcode.com/problems/meeting-rooms-ii/solutions/6555340/
//     c-modern-readable-code-beats-100-runtime-jgq3

// #include <algorithm>
// #include <functional>
// #include <queue>
// #include <vector>

// let 'n' be a cont of intervals
// time complexity O(n * log2(n))
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using Arr2T = std::vector<std::vector<int>>;
    int minMeetingRooms(Arr2T & intervals_) {
        std::sort(intervals_.begin(), intervals_.end());
        mIntervalsEnds = {};
        roomsCount = 0;
        std::for_each(intervals_.cbegin(), intervals_.cend(), roomAllocator);
        return roomsCount;
    }
    Solution():
        roomsCount{0}
    {}
private:
    std::function<void(std::vector<int> const &)> roomAllocator{
        [&] (std::vector<int> const & interval_) {
            if(mIntervalsEnds.empty() ||
                mIntervalsEnds.top() > interval_.front()
            ) {
                ++roomsCount;
            } else {
                mIntervalsEnds.pop();
            }
            mIntervalsEnds.emplace(interval_.back()); 
    }};
    std::priority_queue<int, std::vector<int>, std::greater<int>>
        mIntervalsEnds; 
    int roomsCount;
};
