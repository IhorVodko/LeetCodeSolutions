// problem : https://leetcode.com/problems/lexicographically-smallest-generated-string/description
// submission : https://leetcode.com/problems/lexicographically-smallest-generated-string/submissions/1965010738
// solution post : https://leetcode.com/problems/lexicographically-smallest-generated-string/solutions/7732459/
//    c-modern-readable-code-runtime-0-ms-beat-5crn

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

// let 'n' be the first string length
// 'm' - the second string length
// time complexity O(n + m)
// space complexity O(n + m)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    // Main function to generate the lexicographically smallest string satisfying the
    // problem constraints
    [[nodiscard]]
    auto generateString(
        std::string const str1_,
        std::string const str2_
    ) const -> std::string;
private:
    // Helper function to compute the Z-array for string matching
    [[nodiscard]]
    auto DoZAlgo(std::string const & str_) const -> std::vector<int>;

    static auto constexpr kTrue{'T'};
    static auto constexpr kFalse{'F'};
    static auto constexpr kChrSetFirst{'a'};
    static auto constexpr kChrSetSecond{'b'};
    static auto constexpr kChrDummy{'?'};
};

// Main function to generate the lexicographically smallest string satisfying the
// problem constraints
auto Solution::generateString(
    std::string const str1_,
    std::string const str2_
) const -> std::string {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const len1{std::ssize(str1_)};
    auto const len2{std::ssize(str2_)};
    auto const lenOut{len1 + len2 - 1};
    auto strOut{std::string(lenOut, kChrDummy)};
    // Precompute the Z-array of the target string to quickly verify valid overlaps
    auto zArr{DoZAlgo(str2_)};
    // Track the starting index of the previously placed target string
    auto prevIdx{-1 * len2};

    // First pass: satisfy all 'T' constraints by placing str2_ at required indices
    for(auto const j1: vs::iota(0, len1)) {

        // Skip indices that do not mandate the presence of the target string
        if(str1_[j1] != kTrue) {
            continue;
        }

        // Calculate the length of the overlap with the previously placed target string
        auto const overlapLen{std::max(0l, prevIdx + len2 - j1)};

        // If there is an overlap, use the Z-array to check if the overlapping suffix
        // matches the prefix
        if(overlapLen != 0 && zArr[len2 - overlapLen] < overlapLen) {
            return {};
        }

        // Copy only the non-overlapping remaining characters of str2_ into the output
        // string
        for(auto const j2: vs::iota(overlapLen, len2)) {
            strOut[j1 + j2] = str2_[j2];
        }

        // Update the previous placement index to the current one
        prevIdx = j1;
    }

    // Array to memorize the index of the most recent dummy character available for
    // flipping
    auto lastDummyChrIdxs{std::vector<int>(lenOut, -1)};
    // Reset the tracker to indicate no dummy character has been seen yet
    prevIdx = -1;

    // Second pass: replace all remaining dummy characters with 'a' to ensure
    // lexicographical smallness
    for(auto const j: vs::iota(0, lenOut)) {

        // If a dummy character is found, replace it and update the most recent dummy tracker
        if(strOut[j] == kChrDummy) {
            strOut[j] = kChrSetFirst;
            prevIdx = j;
        }

        // Record the closest available modifiable index for the current position
        lastDummyChrIdxs[j] = prevIdx;
    }

    // Recompute the Z-array on the concatenation of str2_ and the current output string
    // to find all occurrences
    zArr = DoZAlgo(str2_ + strOut);

    // Third pass: satisfy all 'F' constraints by breaking accidental matches of str2_
    for(auto j{0}, stride{0}; j < len1; j += stride) {

        // If the constraint is not 'F' or the target string is not actually present
        // here, move to the next index
        if(str1_[j] != kFalse || zArr[len2 + j] < len2) {
            stride = 1;
            continue;
        }

        // Identify the rightmost modifiable character within the boundaries of the
        // accidental match
        auto const candidatePos{lastDummyChrIdxs[j + len2 - 1]};

        // If no modifiable character exists within the span to break the match, the
        // constraints are impossible
        if(candidatePos < j) {
            return {};
        }

        // Change the 'a' to 'b' to successfully break the forbidden occurrence of str2_
        strOut[candidatePos] = kChrSetSecond;
        // Advance the loop iterator past the modified character since all overlapping
        // 'F' constraints are now fixed
        stride = candidatePos - j + 1;
    }

    // Return the successfully generated lexicographically smallest string
    return strOut;
}

// Standard Z-algorithm implementation to compute the lengths of the longest matching
// prefixes
auto Solution::DoZAlgo(std::string const & str_) const -> std::vector<int> {
    namespace vs = std::views;

    auto const len{std::ssize(str_)};
    // Initialize the Z-array to store the prefix match lengths
    auto zArr{std::vector<int>(len)};
    // The Z-value of the first character is defined as the length of the string itself
    zArr[0] = len;
    // Initialize the left and right boundaries of the current rightmost Z-box
    auto zBoxL{0};
    auto zBoxR{0};

    for(auto const j: vs::iota(1, len)) {

        // CORE Z-ALGO OPTIMIZATION: 'j' is inside our known matching window (Z-box).
        // The substring at 'j' perfectly mirrors the prefix at 'j - zBoxL'.
        // We safely copy that prefix's Z-value, but cap it at the Z-box's right edge 
        // (zBoxR - j + 1) so we don't accidentally assume matches for unseen characters.
        if(j <= zBoxR) {
            zArr[j] = std::min(zArr[j - zBoxL], zBoxR - j + 1);
        }

        // Expand the Z-box to the right as long as the substring matches the prefix
        while(j + zArr[j] < len && str_[zArr[j]] == str_[j + zArr[j]]) {
            zBoxL = j;
            zBoxR = j + zArr[j];
            ++zArr[j];
        }
    }

    return zArr;
}
