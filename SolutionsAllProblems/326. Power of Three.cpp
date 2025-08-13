// problem : https://leetcode.com/problems/power-of-three/description
// submission : https://leetcode.com/problems/power-of-three/submissions/1734033207
// solution post : https://leetcode.com/problems/power-of-three/solutions/7076660/
//    c-modern-readable-code-beats-100-runtime-ocir

// #include <cmath>

namespace Util {
    using intT = std::numeric_limits<int>;
    inline auto constexpr kRadix{10};
    inline auto const kMaxPower{static_cast<int>(std::floor(
        std::log(intT::max()) /
        std::log(3)))};
    inline auto const kMaxPowerOf3{static_cast<int>(std::pow(3, kMaxPower))};
}

class Solution {
public:
// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    bool isPowerOfThree(int const num_) const;
};

bool Solution::isPowerOfThree(int const num_) const {
    using namespace Util;
    if(num_ <= 0) {
        return false;
    }
    auto const isPower{kMaxPowerOf3 % num_ == 0};
    return isPower;
}
