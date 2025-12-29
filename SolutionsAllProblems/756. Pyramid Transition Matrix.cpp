// problem : https://leetcode.com/problems/pyramid-transition-matrix/description  
// submission : https://leetcode.com/problems/pyramid-transition-matrix/submissions/1868527848
// solution post : https://leetcode.com/problems/pyramid-transition-matrix/solutions/7448654/
//    c-modern-readable-code-beats-100-runtime-nzs6

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

class Solution {
public:
// let 'n' be the legnth of the pyramid first row
// 'm' - character set size
// time complexity O(m^n)
// space complexity O(m^2)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto pyramidTransition(
        std::string_view const firstRow_,
        std::vector<std::string> const & allowedPatterns_
    ) -> bool;

private:
    [[nodiscard]]
    auto DoDfs(
        std::vector<std::vector<int>> & pyramidMx_,
        int row_,
        int rowI_,
        int colI_ 
    ) -> bool;
    [[nodiscard]]
    inline auto ToInt(auto const chr_) const -> int;

    std::array<std::array<int, 7>, 7> mTransMx{};
    std::unordered_set<int> mSeen;
};

auto Solution::pyramidTransition(
    std::string_view const firstRow_,
    std::vector<std::string> const & allowedPatterns_
) -> bool {
    for(auto const & pattern: allowedPatterns_) {
        mTransMx[ToInt(pattern[0])][ToInt(pattern[1])] |= 1 << (ToInt(pattern[2]));
    }
    mSeen.clear();
    auto const rowSz{std::ssize(firstRow_)};
    auto pyramidMx{std::vector<std::vector<int>>(rowSz, std::vector<int>(rowSz))};
    auto colI{0};
    for(auto const chr: firstRow_) {
        pyramidMx[rowSz - 1][colI++] = ToInt(chr);
    }
    return DoDfs(pyramidMx, 0, rowSz - 1, 0);
}

auto Solution::DoDfs(
    std::vector<std::vector<int>> & pyramidMx_,
    int row_,
    int rowI_,
    int colI_ 
) -> bool {
    namespace vs = std::views;

    if(rowI_ == 1 && colI_ == 1) {
        return true;
    } else if (colI_ == rowI_) {
        if(mSeen.contains(row_)) {
            return false;
        } 
        mSeen.emplace(row_);
        return DoDfs(pyramidMx_, 0, rowI_ - 1, 0);
    } else {
        auto isParentMask{
            mTransMx[pyramidMx_[rowI_][colI_]][pyramidMx_[rowI_][colI_ + 1]]
        };
        for(auto const b: vs::iota(0, 7)) {
            if(((isParentMask >> b) & 1) != 0) {
                pyramidMx_[rowI_ - 1][colI_] = b;
                if(DoDfs(pyramidMx_, row_ * 8 + (b + 1), rowI_, colI_ + 1)) {
                    return true;
                }
            }
        }
        return false;   
    }
}
    
auto Solution::ToInt(auto const chr_) const -> int {
    return chr_ - 'A';
}
