// problem : https://leetcode.com/problems/longest-common-suffix-queries/description
// submission : https://leetcode.com/problems/longest-common-suffix-queries/submissions/2015495286
// solution post : https://leetcode.com/problems/longest-common-suffix-queries/solutions/8299075/
//    c-modern-readable-code-optimal-time-comp-1jwp

// Approach : Vector-based Reverse Trie (Suffix Tree)
// Runtime : 239 ms, beats 93.52 %

// Complexity
// let 'n' be the count of all characters in in words
// 'm' - count of all characters in queries
// complexity :  O(n + m)
// complexity : O(n)

// import std;

class Solution final {
public:
    using stringsT = std::vector<string>;
    using sizetT = std::numeric_limits<size_t>;

    [[nodiscard]]
    static auto stringIndices(
        stringsT const & words_,
        stringsT const & queries_
    ) -> std::vector<int>;

private:
    static auto constexpr kChrSetSz{26uz};
    static auto constexpr kChrSetFirst{'a'};

    // Stores index of shortest word ending with current suffix path
    struct TrieNode {
        std::array<size_t, kChrSetSz> mChildren{};
        size_t mIdx{sizetT::max()};
    };
};

auto Solution::stringIndices(
    stringsT const & words_,
    stringsT const & queries_
) -> std::vector<int>
{
    namespace vs = std::views;
    namespace rngs = std::ranges;

    // Precompute total capacity to prevent reallocations during Trie build
    auto const wordsChrLen{rngs::fold_left(words_, 0uz, [] (
        auto const accum_,
        auto const & word_
    ) {
        return accum_ + word_.size(); 
    })};

    // Vector-based Trie for better cache locality
    auto trie{std::vector<TrieNode>{}};
    trie.reserve(wordsChrLen + 1);
    trie.emplace_back();

    // Cache lengths for constant time lookups during Trie node updates
    auto const wordLens{
        words_ |
        vs::transform([] (auto const & word_) { return word_.size(); }) |
        rngs::to<std::vector<size_t>>()
    };
    auto const ToIdx{[] (auto const chr_) {
        return static_cast<size_t>(chr_ - kChrSetFirst);
    }};

    for(auto const wordIdx: vs::iota(0uz, words_.size())) {
        auto const wordLen{wordLens[wordIdx]};
        // Tracks the best valid candidate at this suffix depth
        auto const UpdateTrieNodeIdx{[&] (auto const trieIdx_) {
            if( auto & nodeIdx{trie[trieIdx_].mIdx};
                nodeIdx == sizetT::max() || wordLen < wordLens[nodeIdx]
            ) {
                nodeIdx = wordIdx;
            }
        }};
        // Root node holds the shortest word across the entire array
        UpdateTrieNodeIdx(0);

        for(auto currTrieIdx{0uz};
            // Process chars backwards to form a suffix tree structure
            auto const chr: words_[wordIdx] | vs::reverse
        ) {
            auto const childIdx{ToIdx(chr)};
            if( auto & nextTrieIdx{trie[currTrieIdx].mChildren[childIdx]};
                nextTrieIdx == 0
            ) {
                nextTrieIdx = trie.size();
                trie.emplace_back();
            }
            auto const nextTrieIdx{trie[currTrieIdx].mChildren[childIdx]};
            UpdateTrieNodeIdx(nextTrieIdx);
            currTrieIdx = nextTrieIdx;
        }
    }

    // Matches query suffixes against the precomputed Trie
    auto const FindWordIdx{[&] (auto const & query_) {
        auto currTrieIdx{0uz};

        for(auto const chr: query_ | vs::reverse) {
            auto const nextTrieIdx{trie[currTrieIdx].mChildren[ToIdx(chr)]};
            // Stop early if suffix path diverges from available words
            if(nextTrieIdx == 0) {
                break;
            }
            currTrieIdx = nextTrieIdx;
        }

        return static_cast<int>(trie[currTrieIdx].mIdx);
    }};

    return
        queries_ |
        vs::transform(FindWordIdx) |
        rngs::to<std::vector<int>>()
    ;
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
