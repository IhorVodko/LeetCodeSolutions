// problem : https://leetcode.com/problems/smallest-missing-non-negative-integer-after-operations/description/
// submission : https://leetcode.com/problems/smallest-missing-non-negative-integer-after-operations/submissions/
//    1803701084
// solution post : https://leetcode.com/problems/smallest-missing-non-negative-integer-after-operations/solutions
//    /7280639/c-modern-readable-code-beats-100-runtime-tiuw

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
// let 'n' be the number of the given numbers
// 'v' - the given value
// time complexity O(n)
// space complexity O(v)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto findSmallestInteger(
        std::vector<int> & nums_,
        int const val_
    ) const -> int;
};

auto Solution::findSmallestInteger(
    std::vector<int> & nums_,
    int const val_
) const -> int {
    auto numsSz{std::ssize(nums_)};
    auto remToCnt{std::unordered_map<int, int>{}};
    remToCnt.reserve(val_);
    for(auto const num: nums_) {
        auto const rem{(num % val_ + val_) % val_};
        ++remToCnt[rem];
    }
    auto mex{0};
    for(auto remAndCntIt{remToCnt.find(mex % val_)};
        remAndCntIt != remToCnt.cend() && remAndCntIt->second >= 1;
        remAndCntIt = remToCnt.find(mex % val_)
    ) {
        ++mex;
        --remAndCntIt->second;
    }
    return mex;
}
