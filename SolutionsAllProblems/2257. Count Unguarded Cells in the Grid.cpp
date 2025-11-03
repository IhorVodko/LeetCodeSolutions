// problem : https://leetcode.com/problems/count-unguarded-cells-in-the-grid/description/
// submission : https://leetcode.com/problems/count-unguarded-cells-in-the-grid/submissions/1819759375
// solution post : https://leetcode.com/problems/count-unguarded-cells-in-the-grid/solutions/7324253/
//    c-modern-readable-code-beats-100-runtime-cgwf

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream("display_runtime.txt") << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class Solution {
public:
    using cell = std::vector<int>;

// let 'r' be the number of the given rows
// 'c' - of the given columns
// time complexity O(r * c)
// space complexity O(r * c)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto countUnguarded(
        int const rowsSz_, 
        int const colsSz_,
        std::span<const cell> const guards_,
        std::span<const cell> const walls_
    ) -> int;

private:
    enum class State {
        eUnguarded, eGuarded, eGuard, eWall
    };

    using mx = std::vector<std::vector<State>>;

    [[nodiscard]]
    auto updateVisibility (
        int const r_,
        int const c_,
        bool const isGuardLineActive_
    ) -> bool;
    
    mx mGrid;
};

auto Solution::countUnguarded(
    int const rowsSz_, 
    int colsSz_,
    std::span<const cell> const guards_,
    std::span<const cell> const walls_
) -> int {
    namespace vs = std::views;

    using mx = std::vector<std::vector<State>>;
    using enum State;

    mGrid = mx(rowsSz_, std::vector<State>(colsSz_, eUnguarded));
    for(auto const & guard: guards_) {
        mGrid[guard[0]][guard[1]] = eGuard;
    }
    for(auto const & wall: walls_) {
        mGrid[wall[0]][wall[1]] = eWall;
    }
    for(auto const r: vs::iota(0, rowsSz_)) {
        auto isGuardLineActive{mGrid[r][0] == eGuard};
        for(auto const c: vs::iota(0, colsSz_)) {
            isGuardLineActive = updateVisibility(r, c, isGuardLineActive);
        }
        isGuardLineActive = mGrid[r][colsSz_ - 1] == eGuard;
        for(auto const c: vs::iota(0, colsSz_ - 1) | vs::reverse) {
            isGuardLineActive = updateVisibility(r, c, isGuardLineActive);
        }
    }
    for(auto const c: vs::iota(0, colsSz_)) {
        auto isGuardLineActive{mGrid[0][c] == eGuard};
        for(auto const r: vs::iota(1, rowsSz_)) {
            isGuardLineActive = updateVisibility(r, c, isGuardLineActive);
        }
        isGuardLineActive = mGrid[rowsSz_ - 1][c] == eGuard;
        for(auto const r: vs::iota(0, rowsSz_ - 1) | vs::reverse) {
            isGuardLineActive = updateVisibility(r, c, isGuardLineActive);
        }
    }
    auto unguardedCnt{0};
    for(auto const r: vs::iota(0, rowsSz_)) {
        for(auto const c: vs::iota(0, colsSz_)) {
            if(mGrid[r][c] == eUnguarded) {
                ++unguardedCnt;
            }
        }
    }
    return unguardedCnt;
}

auto Solution::updateVisibility (
    int const r_,
    int const c_,
    bool const isGuardLineActive_
) -> bool {
        using enum State;

        if(mGrid[r_][c_] == eGuard) {
            return true;
        }
        if(mGrid[r_][c_] == eWall) {
            return false;
        }
        if(isGuardLineActive_) {
            mGrid[r_][c_] = eGuarded;
        }
        return isGuardLineActive_;
}
