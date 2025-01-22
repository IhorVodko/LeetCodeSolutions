// problem : https://leetcode.com/problems/map-of-highest-peak/description/
// submission : https://leetcode.com/problems/map-of-highest-peak/submissions/1517213146
// solution post : https://leetcode.com/problems/map-of-highest-peak/solutions/6316672/c-modern-readable-code-optimal-time-comp-f207

// #include <limits>
// #include <vector>

// let 'l' be the given matrix length
// let 'w' - width
// time complexity O(l * w)
// space complexity O(1)
// runtime 95 ms, beats 30.34 %
class Solution {
public:
    using Mx = std::vector<std::vector<int>>;
    Mx highestPeak(Mx & isWater ) const {
        FillHeights(isWater);
        DoForwardPass(isWater);
        DoBackwardPass(isWater);
        return isWater;    
    }
    Solution() :
        maxHeight{std::numeric_limits<int>::max() - 1}
    {}
private:
    bool IsWithinMx(
        int const r,
        int const c,
        size_t const rs,
        size_t const cs
    ) const {
        return 0 <= r && r < rs && 0 <= c && c < cs;
    }
    int CalculateMinNeigbourHeight(
        Mx & heights,
        int const r,
        int const c,
        int const neighbourR,
        int const neighbourC
    ) const {
        if(IsWithinMx(neighbourR, neighbourC, heights.size(),
            heights.at(0).size())
        ) {
            return std::min(maxHeight,
                heights.at(neighbourR).at(neighbourC));
        }
        return maxHeight;
    }
    void FillHeights(Mx & heights) const {
        for(auto & row: heights) {
            for(auto & cell: row) {
                cell = cell == 0 ? maxHeight : 0;
            }
        }
    }
    void DoForwardPass(Mx & heights) const {
        for(auto r{0}; r < heights.size(); ++r) {
            for(auto c{0}; c < heights.at(0).size(); ++c) {
                heights.at(r).at(c) = std::min(
                    heights.at(r).at(c),
                    std::min(
                        CalculateMinNeigbourHeight(heights, r, c, r - 1, c),
                        CalculateMinNeigbourHeight(heights, r, c, r, c - 1)
                    ) + 1
                );
            }
        } 
    }
    void DoBackwardPass(Mx & heights) const {
        for(auto r{heights.size() - 1}; r + 1 >= 1; --r) {
            for(auto c{heights.at(0).size() - 1}; c + 1 >= 1; --c) {
                heights.at(r).at(c) = std::min(
                    heights.at(r).at(c),
                    std::min(
                        CalculateMinNeigbourHeight(heights, r, c, r + 1, c),
                        CalculateMinNeigbourHeight(heights, r, c, r, c + 1)
                    ) + 1
                );
            }
        } 
    }
    int maxHeight;
};
