// problem : https://leetcode.com/problems/daily-temperatures/submissions/1547584529/
// submission : https://leetcode.com/problems/daily-temperatures/submissions/1547584529
// solution post : https://leetcode.com/problems/daily-temperatures/solutions/6438540/
//     c-modern-readable-code-optimal-time-comp-zv23

// #include <type_traits>
// #include <vector>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(n)
// runtime 25 ms, beats 50.12 %
class Solution {
public:
    std::vector<int> dailyTemperatures(
        std::vector<int> const & temperatures
    ) const {
        using TempItT = std::remove_cvref<decltype(temperatures)>::type::
            const_iterator;
        auto stack{std::stack<TempItT>()};
        auto daysTillWarmerDay{std::vector<int>(temperatures.size(), 0)};
        for(auto currTempIt{temperatures.begin()},
            tempBeginIt{temperatures.begin()}, tempEndIt{temperatures.end()};
            currTempIt < tempEndIt; ++currTempIt
        ) {
            while(!stack.empty() && *stack.top() < *currTempIt) {
                daysTillWarmerDay.at(stack.top() - tempBeginIt) =
                    currTempIt - stack.top();
                stack.pop();
            }
            stack.push(currTempIt);
        }
        return daysTillWarmerDay;
    }
};
