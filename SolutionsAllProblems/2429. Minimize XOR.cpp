// problem : https://leetcode.com/problems/minimize-xor/description/
// submission : https://leetcode.com/problems/minimize-xor/submissions/1509753524
// solution post : https://leetcode.com/problems/minimize-xor/solutions/6285855/c-modern-readable-code-beats-100-runtime-oii2

// #include<bit>
// #include<bitset>

namespace Utility {
    auto constexpr szInt{sizeof(int) * 8};
}

// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %

class Solution {
public:
    int minimizeXor(
        int const num1,
        int const num2
    ) const {
        using namespace Utility;
        auto const n1{std::bitset<szInt>{ToU(num1)}}; 
        auto ones2{std::popcount(ToU(num2))};
        auto x{std::bitset<szInt>{0}};
        auto idx{szInt - 1};
        auto onesX{size_t{0}};
        while(x.count() < ones2) {
            if(n1.test(idx) || ones2 - x.count() > idx) {
                x.set(idx);
            }
            --idx;
        }
        return x.to_ulong();
    }
private:
    size_t ToU(int const num) const {
        return static_cast<size_t>(num);
    }
};
