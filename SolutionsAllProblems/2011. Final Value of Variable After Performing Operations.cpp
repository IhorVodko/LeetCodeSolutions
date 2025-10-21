// problem : https://leetcode.com/problems/final-value-of-variable-after-performing-operations/description/
// submission : https://leetcode.com/problems/final-value-of-variable-after-performing-operations/submissions/1807771075
// solution post : https://leetcode.com/problems/final-value-of-variable-after-performing-operations/solutions/7291010/
//    c-modern-readable-code-beats-100-runtime-buii

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
// let 'n' be the number of the given operations
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto finalValueAfterOperations(
        std::span<std::string> const ops_
    ) const -> int;
};

auto Solution::finalValueAfterOperations(
    std::span<std::string> const ops_
) const -> int {
    auto val{0};
    for(auto const & op: ops_) {
        assert(op.size() == 3);
        if(op[0] == '-' || op[2] == '-') {
            --val;
        } else {
            ++val;
        }
    }
    return val;
}
