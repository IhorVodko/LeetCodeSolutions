// problem : https://leetcode.com/problems/ways-to-express-an-integer-as-sum-of-powers/description
// submission : https://leetcode.com/problems/ways-to-express-an-integer-as-sum-of-powers/submissions/1732483469
// solution post : https://leetcode.com/problems/ways-to-express-an-integer-as-sum-of-powers/solutions/7071775/
//    c-modern-readable-code-optimal-time-comp-4jpw

// #include <cmath>
// #include <ranges>
// #include <vector>

namespace Util {
    inline auto constexpr kModVal{static_cast<int>(1e9) + 7};
}

class Solution {
public:
// let 'n' be a given target number
// 'p' - given power
// time complexity O(n * root(n, p))
// space complexity O(n)
// runtime 44 ms, beats 79.30 %
    [[nodiscard]]
    int numberOfWays(
        int const targetNum_,
        int const pow_
    ) const;
};

int Solution::numberOfWays(
    int const targetNum_,
    int const pow_
) const {
    namespace views = std::views;
    using namespace Util;
    auto combsCount{std::vector<long long>(targetNum_ + 1, 0)};
    combsCount.at(0) = 1;
    for(auto const num: views::iota(1, targetNum_ + 1)) {
        auto val{static_cast<long long>(std::pow(num, pow_))};
        if(val > targetNum_) {
            break;
        }
        for(auto const reminder:
            views::iota(val, targetNum_ + 1) |
            views::reverse
        ) {
            combsCount.at(reminder) =
                (combsCount.at(reminder) +
                    combsCount.at(reminder - val))
                % kModVal;
        }
    }
    return combsCount.at(targetNum_);
}
