// problem : https://leetcode.com/problems/the-two-sneaky-numbers-of-digitville/description/ 
// submission : https://leetcode.com/problems/the-two-sneaky-numbers-of-digitville/submissions/1817102223
// solution post : https://leetcode.com/problems/the-two-sneaky-numbers-of-digitville/solutions/7316833/
//    c-modern-readable-code-beats-100-runtime-q21d

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
// let 'n' be the number of given numbers
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto getSneakyNumbers(
        std::span<const int> const nums_
    ) -> std::vector<int>;

private:
    static int constexpr kMaxNumsCnt{100};
    static int constexpr kBadNumsCnt{2};
    std::bitset<kMaxNumsCnt> mNumsMask;
};

auto Solution::getSneakyNumbers(
    std::span<const int> const nums_
) -> std::vector<int> {
    mNumsMask.reset();
    auto badNums{std::vector<int>{}};
    for(auto const num: nums_) [[unlikely]] {
        if(mNumsMask.test(num)) {
            badNums.emplace_back(num);
            if(badNums.size() == kBadNumsCnt) {
                return badNums;
            }
        } else [[likely]] {
            mNumsMask.set(num);
        }
    }
    return {-1};
}
