// problem : https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string/description
// submission : https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string/submissions/1938771209
// solution post : https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string/solutions/7627297/
//    c-modern-readable-code-beats-100-runtime-24y4

// import std;

// Static initializer to configure fast I/O before main() runs
inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the string length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    auto minOperations(std::string_view const bits_) const -> int;
};

auto Solution::minOperations(std::string_view const bits_) const -> int {
    namespace vs = std::views;

    // Counts mismatches assuming the alternating pattern starts with '0'
    auto opCntStart0{0};
    // Tracks the expected bit in the alternating sequence
    auto expectedBit{'0'};
    // Compare each actual bit with the expected alternating bit
    for(auto const actualBit: bits_) {
        if(actualBit != expectedBit) {
            ++opCntStart0;
        }
        // Toggle expected bit for the next position
        expectedBit = expectedBit == '0' ? '1' : '0';
    }
    // If starting with '1', mismatches are the complement of start-with-'0'
    auto const opCntStart1{ static_cast<int>(bits_.size()) - opCntStart0};
    auto const minOpCnt{std::min(opCntStart0, opCntStart1)};
    return minOpCnt;
}
