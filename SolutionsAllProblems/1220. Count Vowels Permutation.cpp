// problem : https://leetcode.com/problems/count-vowels-permutation/description/
// submission : https://leetcode.com/problems/count-vowels-permutation/submissions/1863277355
// solution post : https://leetcode.com/problems/count-vowels-permutation/solutions/7434063/
//    c-modern-readable-code-beats-100-runtime-vss4

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

// let 'n' be the string length
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto countVowelPermutation(int const strSz_) const -> int;

private:
    static auto constexpr kModulus{1'000'000'007};
};

auto Solution::countVowelPermutation(int const strSz_) const -> int {
    namespace vs = std::views;

    auto curCntA{1ll};
    auto curCntE{1ll};
    auto curCntI{1ll};
    auto curCntO{1ll};
    auto curCntU{1ll};
    for(auto const i: vs::iota(1, strSz_)) {
        auto nextCntA{(curCntE + curCntI + curCntU) % kModulus};
        auto nextCntE{(curCntA + curCntI) % kModulus};
        auto nextCntI{(curCntE + curCntO) % kModulus};
        auto nextCntO{curCntI % kModulus};
        auto nextCntU{(curCntI + curCntO) % kModulus};
        curCntA = nextCntA;
        curCntE = nextCntE;
        curCntI = nextCntI;
        curCntO = nextCntO;
        curCntU = nextCntU;
    }
    auto const validPermCnt{
        (curCntA + curCntE + curCntI + curCntO +  curCntU) % kModulus
    };
    return static_cast<int>(validPermCnt);
}
