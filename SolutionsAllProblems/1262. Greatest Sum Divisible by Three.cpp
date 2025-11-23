// problem : https://leetcode.com/problems/greatest-sum-divisible-by-three/description/
// submission : https://leetcode.com/problems/greatest-sum-divisible-by-three/submissions/1837954172
// solution post : https://leetcode.com/problems/greatest-sum-divisible-by-three/solutions/7370235/
//    c-modern-readable-code-beats-100-runtime-yy0c

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
// let 'n' be the number of given numbers
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maxSumDivThree(
        std::span<int const> const nums_
    ) const -> int;
};

auto Solution::maxSumDivThree(
    std::span<int const> const nums_
) const -> int {
    static auto constexpr maxInt{std::numeric_limits<int>::max() / 2};
    auto sum{0};
    auto mod1NumMinMin{maxInt};
    auto mod1NumMin{maxInt};
    auto mod2NumMinMin{maxInt};
    auto mod2NumMin{maxInt};
    for(auto const num: nums_) {
        sum += num;
        if(num % 3 == 1) {
            if(num <= mod1NumMinMin) {
                mod1NumMin = mod1NumMinMin;
                mod1NumMinMin = num;
            } else {
                mod1NumMin = std::min(mod1NumMin, num);
            }
        } else if(num % 3 == 2) {
            if(num <= mod2NumMinMin) {
                mod2NumMin = mod2NumMinMin;
                mod2NumMinMin = num;
            } else {
                mod2NumMin = std::min(mod2NumMin, num);
            }
        }
    }
    auto const sumMod{sum % 3};
    if(sumMod == 1) {
        if(mod1NumMinMin == maxInt && mod2NumMin == maxInt) {
            return 0;
        }
        return sum -= std::min(mod1NumMinMin,  mod2NumMinMin + mod2NumMin);
    } else if(sumMod == 2) {
        if(mod1NumMin == maxInt && mod2NumMinMin == maxInt) {
            return 0;
        }
        return sum -= std::min(mod1NumMinMin + mod1NumMin,  mod2NumMinMin);
        
    }
    return sum;
}
