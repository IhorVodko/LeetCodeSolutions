// problem : https://leetcode.com/problems/find-servers-that-handled-most-number-of-requests/description
// submission : https://leetcode.com/problems/find-servers-that-handled-most-number-of-requests/submissions/2192625966
// solution post : https://leetcode.com/problems/find-servers-that-handled-most-number-of-requests/solutions/8607064/
//    simplanation-simple-explanation-by-cyber-fb6p

// Approach : Dual Min-Heap with Modulo Reset
// Runtime : 87 ms, beats 98.43 %

// Complexity analysis
// let 'n' be the number of servers
// 'm' - number of tasks
// Time :  O(m * log(n))
// Space : O(n)

// import std;

// #include <algorithm>
// #include <functional>
// #include <ios>
// #include <iostream>
// #include <optional>
// #include <queue>
// #include <ranges>
// #include <utility>
// #include <vector>
// #include <cstddef>

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

struct BusyServ;

using servIdQueueT = std::priority_queue<int, std::vector<int>, std::greater<>>;
using busyServQueueT =
    std::priority_queue<BusyServ, std::vector<BusyServ>, std::greater<>>;

struct BusyServ final {
    // Track the completion time to know when the server becomes available again.
    int freeAtTime{};
    int servId_{};

    constexpr auto operator<=>(BusyServ const &) const = default;
};

struct TasksProcessingState final {
    TasksProcessingState() = delete;
    
    explicit TasksProcessingState(int const servTot_) :
        taskCntPerServId(servTot_) 
    {
        // Initialize all servers as idle and queue them before the first task.
        auto const servIdRng{vs::iota(0, servTot_)};
        idleServIdsBeforePrefServId = servIdQueueT{
            servIdRng.begin(), servIdRng.end()
        };
    }

    busyServQueueT busyServs;
    servIdQueueT idleServIdsAfterPrefServId;
    servIdQueueT idleServIdsBeforePrefServId;
    std::vector<int> taskCntPerServId;
};

// Optimize standard I/O stream operations performance.
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace 

class Solution final {
public:
    [[nodiscard]]
    static auto busiestServers(
        int const servTot_, 
        std::vector<int> const & taskStartTimes_, 
        std::vector<int> const & taskLoadTimes_
    ) -> std::vector<int>;

private:
    static auto ProcessTask(
        int const servTot_,
        std::vector<int> const & taskStartTimes_, 
        std::vector<int> const & taskLoadTimes_,
        TasksProcessingState & taskProcessingState_,
        int const taskIdx_
    ) -> void;
};

auto Solution::busiestServers(
    int const servTot_, 
    std::vector<int> const & taskStartTimes_, 
    std::vector<int> const & taskLoadTimes_
) -> std::vector<int> {
    const auto tasksTot{static_cast<int>(taskStartTimes_.size())};
    // 1. Iterate through all tasks and sequentially update the server state variables.
    const auto tasksProcessedState{rs::fold_left(
        vs::iota(0, tasksTot),
        TasksProcessingState{servTot_},
        [servTot_, &taskStartTimes_, &taskLoadTimes_] (
            TasksProcessingState taskProcessingState_, 
            int const taskId_
        ) {
            ProcessTask(servTot_, taskStartTimes_, taskLoadTimes_,
                taskProcessingState_, taskId_
            );

            return taskProcessingState_;
        }
    )};

    const auto & taskCntPerServId{tasksProcessedState.taskCntPerServId};
    const auto maxTaskCntPerServId{rs::max(taskCntPerServId)};

    // 2. Filter and collect all server ids matching the maximum processed task count.
    auto busiestServIds{
        vs::iota(0, servTot_) |
        vs::filter([&taskCntPerServId, maxTaskCntPerServId](auto const servId_) {
            const auto servSizeIdx{static_cast<std::size_t>(servId_)};
            return taskCntPerServId[servSizeIdx] == maxTaskCntPerServId;
        }) |
        rs::to<std::vector>()
    };

    return busiestServIds;
}

auto Solution::ProcessTask(
    int const servTot_,
    std::vector<int> const & taskStartTimes_, 
    std::vector<int> const & taskLoadTimes_,
    TasksProcessingState & taskProcessingState_,
    int const taskIdx_
) -> void {
    auto & [busyServs, idleServIdsAfterPrefServId, idleServIdsBeforePrefServId,
        taskCntPerServId
    ]{taskProcessingState_};

    // 1. Calculate preferred server index for the current task using modulo logic.
    const auto prefServId{taskIdx_ % servTot_};

    // Reset the idle queues exactly when the preferred server wraps around to 0.
    if(prefServId == 0) {
        idleServIdsAfterPrefServId = std::move(idleServIdsBeforePrefServId);
        idleServIdsBeforePrefServId = servIdQueueT{};
    }

    const auto taskStartTime{taskStartTimes_[taskIdx_]};
    const auto taskLoadTime{taskLoadTimes_[taskIdx_]};
    
    // 2. Release all servers whose tasks are completed by the current start time.
    while(!busyServs.empty() && busyServs.top().freeAtTime <= taskStartTime) {
        const auto idleServId{busyServs.top().servId_};
        busyServs.pop();

        // Distribute freed servers into correct idle queues relative to prefServId.
        if(idleServId < prefServId) {
            idleServIdsBeforePrefServId.push(idleServId);
        } else {
            idleServIdsAfterPrefServId.push(idleServId);
        }
    }

    // 3. Select the next available server from After queue, or Before queue if empty.
    auto selectedServIdOpt{std::optional<int>{}};

    if(!idleServIdsAfterPrefServId.empty()) {
        selectedServIdOpt = idleServIdsAfterPrefServId.top();
        idleServIdsAfterPrefServId.pop();
    } else if(!idleServIdsBeforePrefServId.empty()) {
        selectedServIdOpt = idleServIdsBeforePrefServId.top();
        idleServIdsBeforePrefServId.pop();
    }

    // Drop the task entirely if no servers are currently idle.
    if(!selectedServIdOpt.has_value()) {
        return;
    }

    const auto selectedServId{selectedServIdOpt.value()};
    
    // 4. Assign task to server, update its processed count, and mark as busy.
    ++taskCntPerServId[selectedServId];

    auto const serverFreeAtTime{taskStartTime + taskLoadTime};
    busyServs.emplace(serverFreeAtTime, selectedServId);
}
