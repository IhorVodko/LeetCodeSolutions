// problem : https://leetcode.com/problems/maximum-average-pass-ratio/description/
// submission : https://leetcode.com/problems/maximum-average-pass-ratio/submissions/1479731946
// solution post : https://leetcode.com/problems/maximum-average-pass-ratio/solutions/6150317/c-modern-readable-code-beats-9587-runtim-yzyr


// #include <algorithm>
// #include <functional>
// #include <queue>
// #include <vector>
// #include <utility>


class Solution {
public:
    using clasItT = std::vector<std::vector<int>>::iterator;
    // let 'n' be a parameter 'classes' length
    // time complexity O(n * log(n))
    // space complexity O(n)
    // runtime 267 ms, beats 95.87 %
    double maxAverageRatio(
        std::vector<std::vector<int>> & classes,
        int extraStudents
    ) const {
        using gainAndClasT = std::pair<double, clasItT>;
        auto gainsMax{std::priority_queue<gainAndClasT,
            std::vector<gainAndClasT>, std::less<gainAndClasT>>{}};
        for(auto clas{classes.begin()}, end{classes.end()}; clas < end; ++clas) {
            gainsMax.push({CalcRatioGain(clas), clas});
        }
        auto gainMax{gainAndClasT{}};
        while(extraStudents-- > 0) {
            gainMax = gainsMax.top();
            std::for_each(gainMax.second->begin(), gainMax.second->end(),
                [&] (auto & num) {++num;});
            gainsMax.pop();
            gainsMax.push({CalcRatioGain(gainMax.second), gainMax.second});
        }
        return std::accumulate(classes.cbegin(), classes.cend(), 0.,
            [&] (auto const init, auto const & clas) {
                return init + static_cast<double>(clas.front()) / clas.back();})
            / classes.size();
    }
private:
        double CalcRatioGain(clasItT clas) const {
            return static_cast<double>(clas->front() + 1) / (clas->back() + 1) -
                static_cast<double>(clas->front()) / clas->back();
        }

};
