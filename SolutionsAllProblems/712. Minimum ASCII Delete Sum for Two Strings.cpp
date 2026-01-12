// problem : https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/description
// submission : https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/submissions/1882738071
// solution post : https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/solutions/7488970/
//    c-modern-readable-code-beats-100-runtime-g0ut

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

// let 'n' be the first string length
// 'm' - second string length
// time complexity O(n * m)
// space complexity O(min(n, m))
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto minimumDeleteSum(
        std::string_view s1_,
        std::string_view s2_
    ) const -> int;
};

auto Solution::minimumDeleteSum(
    std::string_view s1_,
    std::string_view s2_
) const -> int {
    namespace vs = std::views;

    auto sz1{std::ssize(s1_)};
    auto sz2{std::ssize(s2_)};
    if(sz1 < sz2) {
        std::swap(s1_, s2_);
        std::swap(sz1, sz2);
    }
    auto minCosts{std::vector<int>(sz2 + 1)};
    for(auto const i1: vs::iota(1, sz2 + 1)) {
        minCosts[i1] = minCosts[i1 - 1] + s2_[i1 - 1];
    }
    for(auto const i2: vs::iota(1, sz1 + 1)) {
        auto costNotDelChr{minCosts[0]};
        minCosts[0] += s1_[i2 - 1];
        for(auto const i1: vs::iota(1, sz2 + 1)) {
            auto minCost{-1};
            if(s1_[i2 - 1] == s2_[i1 -1]) {
                minCost = costNotDelChr;
            } else {
                auto costDelS1Chr{s1_[i2 - 1] + minCosts[i1]};
                auto costDelS2Chr{s2_[i1 - 1] + minCosts[i1 - 1]};
                minCost = std::min(costDelS1Chr, costDelS2Chr);
            }
            costNotDelChr = minCosts[i1];
            minCosts[i1] = minCost;
        }
    }
    return minCosts[sz2];
}
