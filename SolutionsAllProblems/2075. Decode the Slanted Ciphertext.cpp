// problem : https://leetcode.com/problems/decode-the-slanted-ciphertext/description/
// submission : https://leetcode.com/problems/decode-the-slanted-ciphertext/submissions/1968626603
// solution post : https://leetcode.com/problems/robot-collisions/solutions/7744592/c-modern-readable-code-runtime-0-ms-beat-c1oz

// import std;

// let 'n' be the encoded string length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    // Decode the ciphertext
    [[nodiscard]]
    auto decodeCiphertext(
        // The encoded string
        std::string_view const encStr_,
        // The fixed number of rows used for the cipher
        int const rSz_
    ) const -> std::string;
};

// Decode the ciphertext
auto Solution::decodeCiphertext(
    // The encoded string
    std::string_view const encStr_,
    // The number of rows in the matrix
    int const rSz_
) const -> std::string {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const encStrSz{static_cast<int>(encStr_.size())};
    auto const cSz{encStrSz / rSz_};
    // Calculate the 1D array jump distance to move down-right diagonally
    auto const stride{cSz + 1};
    auto origStr{""s};

    // Resize the string directly writing to its buffer to avoid overhead
    origStr.resize_and_overwrite(encStrSz,
        [&] (char * bufPtr_, [[maybe_unused]] size_t const maxLen_) {
            // Track the current write index in the buffer
            auto wIdx{0uz};

            // Iterate over each starting column to begin a new diagonal sequence
            for(auto const firstC: vs::iota(0, cSz)) {
                // Calculate the exact maximum valid steps to prevent out-of-bounds
                auto const maxStrideCnt{std::min(rSz_, cSz - firstC)};

                // Iterate through the diagonal elements using the pre-calculated step
                // count
                for(auto c{firstC}; auto const step: vs::iota(0, maxStrideCnt)) {
                    bufPtr_[wIdx++] = encStr_[c];
                    // Jump to the next diagonal cell using the flat stride addition
                    c += stride;
                }
            }

            // Check for and remove any phantom padding spaces at the end of the text
            while(wIdx > 0 && bufPtr_[wIdx - 1] == ' ') {
                --wIdx;
            }

            return wIdx;
    });

    return origStr;
}

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
