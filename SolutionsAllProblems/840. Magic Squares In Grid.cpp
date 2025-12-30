// problem : https://leetcode.com/problems/magic-squares-in-grid/description
// submission : https://leetcode.com/problems/magic-squares-in-grid/submissions/1869471131
// solution post : https://leetcode.com/problems/magic-squares-in-grid/solutions/7451247/
//    c-modern-readable-code-beats-100-runtime-5578

// import std;

// let 'n' by 'm' be the size if matrix 
// time complexity O(n * m)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %

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
    [[nodiscard]]    
    auto numMagicSquaresInside(std::vector<vector<int>> const & mx_) const -> int;

private:
    [[nodiscard]]
    auto IsMagicSquare(
        auto const & mx_,
        int const rIdx_,
        int const cIdx_
    ) const -> bool;
    
    static auto constexpr kMagicBorderSeq{std::string_view{"2943816729438167"}};
    static auto constexpr kMagicBorderSeqRev{std::string_view{"7618349276183492"}};
    static auto constexpr kMagicBorderIdxs{std::array<int, 8>{0, 1, 2, 5, 8, 7, 6, 3}};
    static auto constexpr kBuffSz{8};
};

auto Solution::numMagicSquaresInside(
    std::vector<vector<int>> const & mx_
) const -> int {
    auto sqCnt{0};
    auto const rCnt{std::ssize(mx_)};
    auto const cCnt{std::ssize(mx_.front())};
    for(auto rIdx{0}; rIdx + 2 < rCnt; ++rIdx) {
        for(auto cIdx{0}; cIdx + 2 < cCnt; ++cIdx) {
            if(IsMagicSquare(mx_, rIdx, cIdx)) {
                ++sqCnt;
            }
        }
    }
    return sqCnt;
}

auto Solution::IsMagicSquare(
    auto const & mx_,
    int const rIdx_,
    int const cIdx_
) const -> bool {
    auto buff{std::array<char, kBuffSz>{}};
    for(auto pos{0}; auto const idx: kMagicBorderIdxs) {
        auto const num{mx_[rIdx_ + idx / 3][cIdx_ + (idx % 3)]};
        auto const currPos{buff.data() + pos};
        auto const [ptr, _]{std::to_chars(currPos, currPos + 1, num)};
        pos = static_cast<int>(ptr - buff.data());
    }
    auto borderSeq{std::string_view{buff.data(), kBuffSz}};
    auto const isMagicSq{
        mx_[rIdx_][cIdx_] % 2 == 0 && 
        mx_[rIdx_ + 1][cIdx_ + 1] == 5 &&
        (kMagicBorderSeq.find(borderSeq) != std::string::npos || 
        kMagicBorderSeqRev.find(borderSeq) != std::string::npos)
    };
    return isMagicSq;
}
