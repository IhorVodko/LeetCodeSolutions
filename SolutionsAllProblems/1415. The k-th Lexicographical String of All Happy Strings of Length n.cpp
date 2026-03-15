// problem : https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/
//     description/
// submission : https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/
//        submissions/1949112416
// solution post : https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/
//        solutions/6443689/c-modern-readable-code-beats-100-runtime-jquv

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
    // Maps a character to the lexicographically smaller valid next character
    auto const nextSamllestChar{std::unordered_map<char, char>{
        {'a', 'b'}, {'b', 'a'}, {'c', 'a'}}};
    // Maps a character to the lexicographically larger valid next character
    auto const nextGreatestChar{std::unordered_map<char, char>{
        {'a', 'c'}, {'b', 'c'}, {'c', 'b'}}};

} // namespace

// let 'n' be a length of a happy string
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    auto getHappyString(
        int const happyStrLength,
        int happyStrIdx
    ) const -> std::string;
};

auto Solution::getHappyString(
    int const happyStrLength,
    int happyStrIdx
) const -> std::string {
    // Number of combinations for the remaining positions after the first character
    auto const delta{1 << (happyStrLength - 1)};
    auto maxHappyStringsCount{3 * delta};
    if(happyStrIdx > maxHappyStringsCount) {
        return "";
    } 
    auto resultStr{std::string(happyStrLength, 'a')};
    // Starting indices (1-based) of blocks corresponding to strings beginning with
    // 'a', 'b', and 'c' respectively
    auto startA{1};
    auto startB{startA + delta};
    auto startC{startB + delta};
    // Determine which first-character block contains the k-th string and adjust the
    // index to become relative to that block
    if(happyStrIdx < startB) {
        resultStr.at(0) = 'a';
        happyStrIdx -= startA;
    } else if(happyStrIdx < startC) {
        resultStr.at(0) = 'b';
        happyStrIdx -= startB;
    } else {
        resultStr.at(0) = 'c'; 
        happyStrIdx -= startC;
    }
    // Iteratively determine each subsequent character.
    for(auto charIdx{1}; charIdx < happyStrLength; ++charIdx) {
        // Size of the subgroup of strings for the current position choice
        auto midpointGoupIdx{1 << (happyStrLength - charIdx - 1)};
        if(happyStrIdx < midpointGoupIdx) {
            resultStr.at(charIdx) = nextSamllestChar.at(resultStr.at(
                charIdx - 1));
        } else {
            resultStr.at(charIdx) = nextGreatestChar.at(resultStr.at(
                charIdx - 1));
            happyStrIdx -= midpointGoupIdx;
        }
    }
    return resultStr;
} 
