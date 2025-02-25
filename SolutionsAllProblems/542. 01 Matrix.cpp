// problem : https://leetcode.com/problems/01-matrix/description/
// submission : https://leetcode.com/problems/01-matrix/submissions/1555296221
// solution post : https://leetcode.com/problems/01-matrix/solutions/6467568/
//     c-modern-readable-code-optimal-time-comp-gd28

// #include <queue>
// #include <vector>

namespace Constants {
    auto constexpr moves{std::array<std::pair<int, int>, 4>{{
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}  
    }}};
    auto constexpr source{0};
    auto constexpr destination{1};
}

// let 'n' and 'm' be dimensions of the given matrix
// time complexity O(n * m)
// space complexity O(n * m)
// runtime 12 ms, beats 82.30 %
class Solution {
public:
    using MxT = std::vector<std::vector<int>>;
    using CellT = std::pair<int, int>;
    MxT updateMatrix(MxT & mx) const {
        using namespace Constants; 
        auto cells{std::queue<CellT>{}}; 
        auto const rowsCount{mx.size()};
        auto const colsCount{mx.at(0).size()};
        for(auto row{0}; row < rowsCount; ++row) {
            for(auto col{0}; col < colsCount; ++col) {
                if(mx[row][col] == source) {
                    cells.emplace(row, col);
                }
            }
        }
        FindMinimumDistances(mx, cells);
        AdjustBackDistances(mx);
        return mx;
    }
private:
    bool IsCellWithinMatrix(
        CellT const & cell,
        MxT const & mx
    ) const {
        auto const [row, col]{cell};
        auto const rowsCount{mx.size()};
        auto const colsCount{mx.at(0).size()};
        return 0 <= row && row < rowsCount && 0 <= col && col < colsCount;
    }
    void AdjustBackDistances(MxT & mx) const {
        using namespace Constants;
        auto const rowsCount{mx.size()};
        auto const colsCount{mx.at(0).size()};
        for(auto row{0}; row < rowsCount; ++row) {
            for(auto col{0}; col < colsCount; ++col) {
                if(mx[row][col] != source) {
                    --mx[row][col];
                }
            }
        }
    }
    void FindMinimumDistances(
        MxT & mx,
        std::queue<CellT> & cells
    ) const {
        using namespace Constants;
        auto distance{1};
        while(!cells.empty()) {
            ++distance;
            auto levelSize{cells.size()};
            while(levelSize-- > 0) {
                auto const [rowCurr, colCurr]{cells.front()};
                cells.pop();
                for(auto const & move: moves) {
                    auto rowNext{rowCurr + move.first};
                    auto colNext{colCurr + move.second};
                    if(IsCellWithinMatrix({rowNext, colNext}, mx) &&
                        mx[rowNext][colNext] == destination
                    ) {
                        mx[rowNext][colNext] = distance;            
                        cells.emplace(rowNext, colNext);
                    }
                }
            }
        }
    }    
};
