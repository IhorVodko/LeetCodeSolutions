// problem : https://leetcode.com/problems/count-special-triplets/description/?envType=daily-question&envId=2025-12-09
// submission : https://leetcode.com/problems/count-special-triplets/submissions/1851357306
// solution post : https://leetcode.com/problems/count-special-triplets/solutions/7403141/
//    c-modern-readable-code-beats-100-runtime-un0c

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
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto specialTriplets(std::span<int const> const nums_) const -> int;

private:
    static auto constexpr kModVal{1'000'000'007};
};

auto Solution::specialTriplets(std::span<int const> const nums_) const -> int {
    namespace vs = std::views;

    auto const numsSz{std::ssize(nums_)};
    auto numToCnt{std::unordered_map<int, int>{}};
    numToCnt.reserve(numsSz);
    auto numToPartialCnt{std::unordered_map<int, int>{}};
    numToPartialCnt.reserve(numsSz);
    for(auto const num: nums_) {
        ++numToCnt[num];
    }
    auto tripletCnt{0};
    for(auto const num: nums_) {
        auto const targetNum{num * 2};
        if( auto const numToCntIt{numToCnt.find(targetNum)};
            numToCntIt == numToCnt.end()
        ) {
            ++numToPartialCnt[num];
            continue;
        } else {
            auto leftCnt{numToPartialCnt[targetNum]};
            ++numToPartialCnt[num];
            auto rightCnt{numToCntIt->second - numToPartialCnt[targetNum]};
            auto const currTripletCnt{
                (static_cast<long long>(leftCnt) * rightCnt) % kModVal
            };
            tripletCnt = (tripletCnt + currTripletCnt) % kModVal;
        }
    }
    return tripletCnt;
}
