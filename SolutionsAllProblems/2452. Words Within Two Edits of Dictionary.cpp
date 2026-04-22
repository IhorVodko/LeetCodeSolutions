// problem : https://leetcode.com/problems/words-within-two-edits-of-dictionary/description/
// submission : https://leetcode.com/problems/words-within-two-edits-of-dictionary/submissions/1985507369
// solution post : https://leetcode.com/problems/words-within-two-edits-of-dictionary/solutions/8057117/
//    c-modern-readable-code-beats-100-runtime-ug90

// Approach : Brute Force with Early Stopping
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the number of queries
// 'm' - dictionary size
// 'k' - word length
// complexity :  O(n * m * k)
// complexity : O(1)

// import std;

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


class Solution final {
public:
    using wordsT = std::vector<string>;

    [[nodiscard]]
    auto twoEditWords(
        wordsT const & queries, 
        wordsT const & dictionary
    ) const -> wordsT;

private:
    // Constant defining the maximum allowed edits
    static auto constexpr kMaxEditCnt{2};
};

auto Solution::twoEditWords(
    wordsT const & queries, 
    wordsT const & dictionary
) const -> wordsT {
    namespace vs = std::views;

    // Vector to store matching query words
    auto matchedWords{wordsT{}};

    auto const wordLen{std::ssize(queries.front())};

    for(auto const & query: queries) {
        for(auto const & target: dictionary) {
            auto editCnt{0};
            auto isMatch{true};

            for(auto const j: vs::iota(0, wordLen)) {
                if(query[j] == target[j]) {
                    // Skip counting, characters match
                    continue;
                }
                
                if(++editCnt > kMaxEditCnt) {
                    isMatch = false;

                    // Stop checking remaining characters
                    break;
                }
            }

            if(isMatch) {
                matchedWords.emplace_back(query);

                // Stop checking other dictionary words for this query
                break;
            }
        }
    }

    return matchedWords;
}
