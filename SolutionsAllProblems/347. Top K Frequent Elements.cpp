// problem : https://leetcode.com/problems/top-k-frequent-elements/submissions/1507717585/  
// submission : https://leetcode.com/problems/top-k-frequent-elements/submissions/1507717585
// solution post : https://leetcode.com/problems/top-k-frequent-elements/solutions/6275992/c-modern-readable-code-optimal-time-comp-3b6l

// #include <functional>
// #include <queue>
// #include <vector>
// #include <unordered_map>

// let 'u' be a count of unique numbers in parameter 'nums'
// time complexity O(u * log(u))
// space complexity O(u)
// runtime 3 ms, beats 57.71 %
class Solution {
public:
    using ItT = std::map<int, size_t>::const_iterator;
    std::vector<int> topKFrequent(
        std::vector<int>& nums,
        int const k
    ) const {
        auto numsToCounts{std::map<int, size_t>{}};
        for(auto const num: nums) {
            ++numsToCounts[num];
        }    
        auto heapMax{std::priority_queue{compare, std::vector<ItT>{}}};
        for(auto numToCount{numsToCounts.cbegin()}, end{numsToCounts.cend()}; 
            numToCount != end; ++numToCount
        ) {
            heapMax.push(numToCount);
        }
        auto topKNums{std::vector<int>{}};
        topKNums.reserve(k);
        while(topKNums.size() < k) {
            topKNums.emplace_back(heapMax.top()->first);
            heapMax.pop();
        }
        return topKNums;
    }
private:
    std::function<bool(ItT const lhs, ItT const rhs)> compare{
        [] (auto lhs, auto rhs) { return lhs->second < rhs->second; }};
};
