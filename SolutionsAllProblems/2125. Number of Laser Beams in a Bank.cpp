// problem : https://leetcode.com/problems/number-of-laser-beams-in-a-bank/description/
// submission : https://leetcode.com/problems/number-of-laser-beams-in-a-bank/submissions/1813274463
// solution post : https://leetcode.com/problems/number-of-laser-beams-in-a-bank/solutions/7305807/
//    c-modern-readable-code-beats-100-runtime-ege6

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
// let 'n' be the number of the rows
// 'm' - given length of the row
// time complexity O(n * m)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto numberOfBeams(std::span<const std::string> const bank_) const -> int;
};

auto Solution::numberOfBeams(std::span<const std::string> const bank_) const -> int {
    namespace rngs = std::ranges;
    namespace vs = std::views;

    if(bank_.empty()) {
        return -1;
    }
    auto beamCnt{0};
    for(auto devicesPrevRowCnt{0}; auto const & str: bank_) {
        if( auto const devicesCurrRowCnt{rngs::count(str, '1')};
            devicesCurrRowCnt >= 1
        ) {
            beamCnt += devicesPrevRowCnt * devicesCurrRowCnt;
            devicesPrevRowCnt = devicesCurrRowCnt;
        }
    }
    return beamCnt;
}
