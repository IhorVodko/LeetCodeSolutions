// problem : https://leetcode.com/problems/set-matrix-zeroes/description/
// submission : https://leetcode.com/problems/set-matrix-zeroes/submissions/1640396055
// solution post : https://leetcode.com/problems/set-matrix-zeroes/solutions/6767343/
//    c-modern-readable-code-beats-100-by-cybe-69pq

// #include <algorithm>
// #include <vector>

class Solution {
public:
    using Arr2T = std::vector<std::vector<int>>;
// let 'w' by 'l' be dimensions of the given matrix 
// time complexity O(w * l)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    void setZeroes(Arr2T & mx_);
};

void Solution::setZeroes(Arr2T & mx_) {
    auto const rowsCount{mx_.size()};
    auto const colsCount{mx_.at(0).size()};
    auto isPresentZeroAtFirstRow{
        std::find(mx_.at(0).cbegin(), mx_.at(0).cend(), 0) == mx_.at(0).cend() ?
        false : true};
    auto isPresentZeroAtFirstCol{false};
    for(auto & row: mx_) {
        if(row.at(0) == 0) {
            isPresentZeroAtFirstCol = true;
        }
    }
    for(auto r{0}; r < rowsCount; ++r) {
        for(auto c{0}; c < colsCount; ++c) {
            if(mx_[r][c] == 0) {
                mx_[r][0] = 0;
                mx_[0][c] = 0;
            }
        }
    }
    for(auto c{1}; c < colsCount; ++c) {
        if(mx_[0][c] == 0) {
            for(auto & row: mx_) {
                row[c] = 0;
            }
        }
    }
    for(auto r{1}; r < rowsCount; ++r) {
        if(mx_[r].at(0) == 0) {
            std::fill(mx_[r].begin(), mx_[r].end(), 0);
        }
    }
    if(isPresentZeroAtFirstRow) {
        std::fill(mx_.at(0).begin(), mx_.at(0).end(), 0);
    }
    if(isPresentZeroAtFirstCol) {
        for(auto & row: mx_) {
            row.at(0) = 0;
        }
    }
}
