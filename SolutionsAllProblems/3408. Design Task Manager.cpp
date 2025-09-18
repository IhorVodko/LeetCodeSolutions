// problem : https://leetcode.com/problems/design-task-manager/description/
// submission : https://leetcode.com/problems/design-task-manager/submissions/1775213556
// solution post : https://leetcode.com/problems/design-task-manager/solutions/7203035/
//    c-modern-readable-code-optimal-time-comp-ax7b

// import std;

/**
 * Your TaskManager object will be instantiated and called as such:
 * TaskManager* obj = new TaskManager(tasks);
 * obj->add(userId,taskId,priority);
 * obj->edit(taskId,newPriority);
 * obj->rmv(taskId);
 * int param_4 = obj->execTop();
 */

// let 't' be a count of the given tasks
// 'c' - count of the method calls 
// time complexity O(t + c * log(t))
// space complexity O(t)
// runtime 372 ms, beats 43.75 %
class TaskManager {
public:
    TaskManager(std::vector<std::vector<int>> const & tasks_);
    auto add(
        int const user_,
        int const task_,
        int const priority_
    ) -> void;
    auto edit(
        int const task_,
        int const newPriority_
    ) -> void;
    auto rmv(auto const task_) -> void;
    auto execTop() -> int;

private:
    static inline bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
    std::map<int, std::set<int>> mPriorityToTasks;
    std::unordered_map<int, std::pair<int, int>> mTaskToUserAndPriority;
};

TaskManager::TaskManager(std::vector<std::vector<int>> const & tasks_) {
    for(auto const &  taskData: tasks_) {
        auto const user{taskData.at(0)};
        auto const task{taskData.at(1)};
        auto const priority{taskData.at(2)};
        add(user, task, priority);
    }
}

auto TaskManager::add(
    int const user_,
    int const task_,
    int const priority_
) -> void {
    assert(!mPriorityToTasks[priority_].contains(task_));
    mPriorityToTasks[priority_].emplace(task_);
    assert(!mTaskToUserAndPriority.contains(task_));
    mTaskToUserAndPriority[task_] = {user_, priority_};
}

auto TaskManager::edit(
    int const task_,
    int const newPriority_
) -> void {
    auto const oldPriority{mTaskToUserAndPriority.at(task_).second};
    assert(mPriorityToTasks.at(oldPriority).contains(task_));
    mPriorityToTasks.at(oldPriority).erase(task_);
    if(mPriorityToTasks.at(oldPriority).empty()) {
        mPriorityToTasks.erase(oldPriority);
    }
    mPriorityToTasks[newPriority_].emplace(task_);
    mTaskToUserAndPriority.at(task_).second = newPriority_;
}

auto TaskManager::rmv(auto const task_) -> void {
    auto const oldPriority{mTaskToUserAndPriority.at(task_).second};
    assert(mPriorityToTasks.at(oldPriority).contains(task_));
    mPriorityToTasks.at(oldPriority).erase(task_);
    if(mPriorityToTasks.at(oldPriority).empty()) {
        mPriorityToTasks.erase(oldPriority);
    }
    assert(mTaskToUserAndPriority.contains(task_));
    mTaskToUserAndPriority.erase(task_);
}

auto TaskManager::execTop() -> int {
    if(mPriorityToTasks.empty()) {
        return -1;
    }
    auto const maxPriority{(--mPriorityToTasks.end())->first};
    auto const maxTask{*(--mPriorityToTasks.at(maxPriority).end())};
    assert(mPriorityToTasks.at(maxPriority).contains(maxTask));
    mPriorityToTasks.at(maxPriority).erase(maxTask);
    if(mPriorityToTasks.at(maxPriority).empty()) {
        mPriorityToTasks.erase(maxPriority);
    }
    auto maxUser{mTaskToUserAndPriority.at(maxTask).first};
    assert(mTaskToUserAndPriority.contains(maxTask));
    mTaskToUserAndPriority.erase(maxTask);
    return maxUser;
}
