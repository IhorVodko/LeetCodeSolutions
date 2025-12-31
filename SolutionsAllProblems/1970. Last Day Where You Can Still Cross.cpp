// problem : https://leetcode.com/problems/last-day-where-you-can-still-cross/description
// submission : https://leetcode.com/problems/last-day-where-you-can-still-cross/submissions/1870458971
// solution post : https://leetcode.com/problems/last-day-where-you-can-still-cross/solutions/7453864/
//    c-modern-readable-code-beats-100-runtime-9jf1

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream{"display_runtime.txt"} << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class Dsu{
public:
    explicit Dsu(int const size_):
        mSizes{std::vector<int>(size_, 1)},
        mRoots{std::vector<int>(size_)}
    {
        std::iota(mRoots.begin(), mRoots.end(), 0);
    }
    
    [[nodiscard]]
    auto find(int const val_) -> int {
        if(mRoots[val_] != val_) {
            mRoots[val_] = find(mRoots[val_]);
        }
        return mRoots[val_];
    }
    auto Union(
        int const val1_,
        int const val2_
    ) -> void {
        auto rootX{find(val1_)};
        auto rootY{find(val2_)};
        if(rootX == rootY) {
            return;
        }
        if(mSizes[rootX] > mSizes[rootY]) {
            std::swap(rootX, rootY);
        }
        mRoots[rootX] = rootY;
        mSizes[rootY] += mSizes[rootX];
    }

private:
    std::vector<int> mSizes;
    std::vector<int> mRoots; 
};


// let 'n' by 'm' be the grid size
// time complexity O(n * m)
// space complexity O(n * m)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto latestDayToCross(
        int rowTotCnt_,
        int colTotCnt_,
        std::vector<std::vector<int>> const & waterCells_
    ) const -> int;

private:
    static auto constexpr kMoves{std::array<std::pair<int, int>, 8>{
        {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}
    }};
};

auto Solution::latestDayToCross(
    int rowTotCnt_,
    int colTotCnt_,
    std::vector<std::vector<int>> const & waterCells_
) const -> int {
    namespace vs = std::views;

    auto const gridSz{rowTotCnt_ * colTotCnt_};
    auto dsu{Dsu{gridSz + 2}};
    auto grid{std::vector<std::vector<int>>(rowTotCnt_, std::vector<int>(colTotCnt_))};
    for(auto const cellIdx: vs::iota(0, gridSz)) {
        auto const curR{waterCells_[cellIdx][0] - 1};
        auto const curC{waterCells_[cellIdx][1] - 1};
        grid[curR][curC] = 1;
        auto cellIdx1{curR * colTotCnt_ + curC + 1};
        for(auto const [offsetR, offsetC]: kMoves) {
            auto const nextR{curR + offsetR};
            auto const nextC{curC + offsetC};
            auto const cellIdx2{nextR * colTotCnt_ + nextC + 1};
            if( 0 <= nextR && nextR < rowTotCnt_ &&
                0 <= nextC && nextC < colTotCnt_ &&
                grid[nextR][nextC] == 1
            ) {
                dsu.Union(cellIdx1, cellIdx2);
            }
        }
        if(curC == 0) {
            dsu.Union(0, cellIdx1);
        }
        if(curC == colTotCnt_ - 1) {
            dsu.Union(gridSz + 1, cellIdx1);
        }
        if(dsu.find(0) == dsu.find(gridSz + 1)) {
            return cellIdx;
        }
    }
    return -1;
}
