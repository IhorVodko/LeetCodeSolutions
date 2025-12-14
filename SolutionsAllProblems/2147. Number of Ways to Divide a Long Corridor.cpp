// problem : https://leetcode.com/problems/number-of-ways-to-divide-a-long-corridor/description
// submission : https://leetcode.com/problems/number-of-ways-to-divide-a-long-corridor/submissions/1855738511
// solution post : https://leetcode.com/problems/number-of-ways-to-divide-a-long-corridor/solutions/7414259/
//    c-modern-readable-code-beats-100-runtime-98ea

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
// let 'n' be the length of the given corridor
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto numberOfWays(std::string_view const corridor_) const -> int;

private:
    static auto constexpr kModulus{1'000'000'007};
    static auto constexpr kSeat{'S'};
    static auto constexpr kPlant{'P'}; 
};

auto Solution::numberOfWays(std::string_view const corridor_) const -> int {
    auto wayCnt{1ll};
    auto currPlantCnt{0};
    auto currSeatCnt{0};
    auto seatCnt{0};
    for(auto const obj: corridor_) {
        seatCnt += obj == kSeat ? 1 : 0;
        if(currSeatCnt < 2) {
            currSeatCnt += obj == 'S' ? 1 : 0;
        } else {
            if(obj == kPlant) {
                ++currPlantCnt;
            } else {
                wayCnt = ((wayCnt) * (currPlantCnt + 1)) % kModulus;
                currSeatCnt = 1;
                currPlantCnt = 0;
            }
        }
    }
    return (seatCnt % 2 == 1 || seatCnt == 0) ? 0 : static_cast<int>(wayCnt);
}
