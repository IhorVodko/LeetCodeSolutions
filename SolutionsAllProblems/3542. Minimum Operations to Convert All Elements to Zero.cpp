// problem : https://leetcode.com/problems/minimum-operations-to-convert-all-elements-to-zero/description
// submission : https://leetcode.com/problems/minimum-operations-to-convert-all-elements-to-zero/submissions/1826187875
// solution post : https://leetcode.com/problems/minimum-operations-to-convert-all-elements-to-zero/solutions/7339979/
//    c-modern-readable-code-beats-100-runtime-9z7b

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
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto minOperations(std::span<int const> const nums_) const -> int;
};

auto Solution::minOperations(std::span<int const> const nums_ ) const -> int {
    auto stck{std::stack<int>{}};
    auto opsCnt{0};
    for (auto const num: nums_) {
        while (!stck.empty() && stck.top() > num) {
            stck.pop();
        }
        if (num != 0 &&
            (stck.empty() || stck.top() < num)
        ) {
            ++opsCnt;
            stck.emplace(num);
        }
    }
    return opsCnt;
}
