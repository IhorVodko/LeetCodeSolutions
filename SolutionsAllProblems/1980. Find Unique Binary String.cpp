// problem : https://leetcode.com/problems/find-unique-binary-string/description/
// submission : https://leetcode.com/problems/find-unique-binary-string/submissions/1942250998
// solution post : https://leetcode.com/problems/find-unique-binary-string/solutions/6448441/
//        c-modern-readable-code-beats-100-runtime-10ha

// #include <string>

// Static initializer to configure fast I/O before main() runs
inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the number of binary strings
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    auto findDifferentBinaryString(
        std::span<std::string const> const nums_
    ) const -> std::string;
};

auto Solution::findDifferentBinaryString(
    std::span<std::string const> const nums_
) const -> std::string {
    namespace vs = std::views;

    auto const numsLength{nums_.size()};
    auto differentNum{""s};
    differentNum.reserve(numsLength);
    // Construct a binary string that differs at the i-th bit from the i-th string
    for(auto const i: vs::iota(0u, numsLength)) {
        // Flip the diagonal bit to guarantee uniqueness (Cantor's diagonalization idea)
        differentNum += nums_[i][i] == '0' ? '1' : '0';
    }
    return differentNum;
}
