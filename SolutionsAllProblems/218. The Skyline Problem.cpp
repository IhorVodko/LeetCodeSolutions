// problem : https://leetcode.com/problems/the-skyline-problem/description/
// submission : https://leetcode.com/problems/the-skyline-problem/submissions/1765060634
// solution post : https://leetcode.com/problems/the-skyline-problem/solutions/7172788/
//    c-modern-readable-code-optimal-time-comp-zn1s

// #include <algorithm>
// #include <utility>
// #include <vector>

class Solution {
public:
    using buildingT = std::vector<int>;
    using buildingsT = std::vector<buildingT>;
// let 'n' be a count of the buildings given
// time complexity O(n * log(n))
// space complexity O(n)
// runtime 11 ms, beats 88.55 %
    [[nodiscard]]
    buildingsT getSkyline(buildingsT const & buildings_) const;
};

Solution::buildingsT Solution::getSkyline(buildingsT const & buildings_) const {
    namespace ranges = std::ranges;
    auto edges{std::vector<std::pair<int, int>>{}};
    for(auto const & building: buildings_) {
        edges.emplace_back(building.at(0), building.at(2));
        edges.emplace_back(building.at(1), -1 * building.at(2));
    }
    ranges::sort(edges);
    auto currBuildings{std::priority_queue<int>{}};
    auto removedBuildings{std::priority_queue<int>{}};
    auto points{std::vector<std::vector<int>>{}};
    auto idx{0};
    auto const edgesSz{edges.size()};
    while(idx < edgesSz) {
        auto const x{edges.at(idx).first};
        while(idx < edgesSz && edges.at(idx).first == x) {
            auto const height{edges.at(idx).second};
            height > 0 ?
                currBuildings.emplace(height) :
                removedBuildings.emplace(-1 * height);
            ++idx;
        }
        while(
            !removedBuildings.empty() &&
            currBuildings.top() == removedBuildings.top()
        ) {
            currBuildings.pop();
            removedBuildings.pop();
        }
        auto const currHeight{currBuildings.empty() ? 0 : currBuildings.top()};
        if(points.empty() || points.back().at(1) != currHeight) {
            points.emplace_back(std::initializer_list{x, currHeight});
        }
    }
    return points;
}
