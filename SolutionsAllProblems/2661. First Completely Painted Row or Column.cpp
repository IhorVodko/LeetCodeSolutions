// problem : https://leetcode.com/problems/first-completely-painted-row-or-column/description/
// submission : https://leetcode.com/problems/first-completely-painted-row-or-column/submissions/1514985793
// solution post : https://leetcode.com/problems/first-completely-painted-row-or-column/solutions/6308191/c-modern-readable-code-optimal-time-comp-ijnw

// #include <vector>
// #include <unordered_map>

// let 'l' be a length of a given matrix
// 'w' - width of a given matrix
// time complexity O(l * w)
// space complexity O(l * w)
// runtime 107 ms, beats 42.07 %
class Solution {
public:
    using D1 = std::vector<int>;
    using D2 = std::vector<D1>;
    int firstCompleteIndex(
        D1 const & arr,
        D2 const & mx
    ) const {
        auto const rows{mx.size()};
        auto const cols{mx.at(0).size()};
        auto numsToPoss{std::unordered_map<int, std::pair<size_t, size_t>>{}};
        for(auto row{size_t{0}}; row < rows; ++row) {
            for(auto col{size_t{0}}; col < cols; ++col) {
                numsToPoss.insert({mx.at(row).at(col), {row, col}});
            }
        }
        auto rowsCellsPainted{std::vector<size_t>(rows, 0)};
        auto colsCellsPainted{std::vector<size_t>(cols, 0)};
        for(auto i{size_t{0}}; i < arr.size(); ++i) {
            if(++rowsCellsPainted.at(numsToPoss.at(arr.at(i)).first) == cols ||
                ++colsCellsPainted.at(numsToPoss.at(arr.at(i)).second) == rows
            ) {
                return i;
            } 
        }
        return -1; 
    }
};
