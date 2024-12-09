// problem : https://leetcode.com/problems/two-best-non-overlapping-events/description/
// submission : https://leetcode.com/problems/two-best-non-overlapping-events/submissions/1474592202
// solution post : https://leetcode.com/problems/two-best-non-overlapping-events/solutions/6130182/c-modern-readable-code


// #include <algorithm>
// #include <array>
// #include <vector>

class Solution {
public:
    // let 'n' be an input array length
    // time complexity O(n * log(n))
    // space complexity O(n)
    // runtime 65 ms, beats 67.67 %
    int maxTwoEvents(
        std::vector<std::vector<int>> & events
    ) {
        startEndTimes.reserve(events.size() * 2);
        for(auto const & event : events) {
            startEndTimes.push_back({event.at(0), 1, event.at(2)});
            startEndTimes.push_back({event.at(1) + 1, 0, event.at(2)});
        }
        std::sort(startEndTimes.begin(), startEndTimes.end());
        for(auto const & startEndTime : startEndTimes) {
            startEndTime.at(1) ?
                maxSum = std::max(maxSum, startEndTime.at(2) + maxVal) :
                maxVal = std::max(maxVal, startEndTime.at(2));
        }
        return maxSum;
    }
private:
    std::vector<std::array<int, 3>> startEndTimes;
    int maxSum{0};
    int maxVal{0};
};
