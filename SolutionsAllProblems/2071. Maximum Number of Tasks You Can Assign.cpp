// problem : https://leetcode.com/problems/maximum-number-of-tasks-you-can-assign/description/
// submission : https://leetcode.com/problems/maximum-number-of-tasks-you-can-assign/submissions/1624439132
// solution post : https://leetcode.com/problems/maximum-number-of-tasks-you-can-assign/solutions/6710963/
//    c-modern-readable-code-optimal-time-comp-r8l0

// #include <algorithm>
// #include <deque>
// #include <vector>

// let 't' be a count of tasks given
// 'w' - count of workers given 
// time complexity O(t * log(t) + w * log(w))
// space complexity O(log(t) + log(w) + min(t, w))
// runtime 83 ms, beats 75.92 %
class Solution {
public:
    int maxTaskAssign(
        std::vector<int> & tasks_,
        std::vector<int> & workers_,
        int pillsCount_,
        int const strength_
    ) const;
};

int Solution::maxTaskAssign(
    std::vector<int> & tasks_,
    std::vector<int> & workers_,
    int pillsCount_,
    int const strength_
) const {
    auto const tasksCount{static_cast<int>(tasks_.size())};
    auto const workersCount{static_cast<int>(workers_.size())};
    std::sort(tasks_.begin(), tasks_.end());
    std::sort(workers_.begin(), workers_.end());
    auto IsAssignmentPossible{[&] (int const mid) {
        auto pillsCount{pillsCount_};
        auto workersLeft{std::deque<int>{}};
        auto workerIdx{workersCount - 1};
        for(auto idx{mid - 1}; idx >= 0; --idx) {
            while(workerIdx >= workersCount - mid && 
                workers_.at(workerIdx) + strength_ >= tasks_.at(idx)
            ) {
                workersLeft.emplace_front(workers_.at(workerIdx));
                --workerIdx;
            }
            if(workersLeft.empty()) {
                return false;
            } else if(workersLeft.back() >= tasks_.at(idx)) {
                workersLeft.pop_back();
            } else {
                if(!pillsCount) {
                    return false;
                }
                --pillsCount;
                workersLeft.pop_front();
            }
        }
        return true;
    }};
    auto left{1};
    auto right{std::min(tasksCount, workersCount)};
    auto tasksCountMax{0};
    while(left <= right) {
        auto const mid{left + (right - left) / 2};
        if(IsAssignmentPossible(mid)) {
            tasksCountMax = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return tasksCountMax;
}
