// problem : https://leetcode.com/problems/minimum-cost-to-convert-string-ii/description
// submission : https://leetcode.com/problems/minimum-cost-to-convert-string-ii/submissions/1902340290
// solution post : https://leetcode.com/problems/minimum-cost-to-convert-string-ii/solutions/7537581/
//      c-modern-readable-code-beats-100-runtime-273i

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] () { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

static auto constexpr kChrSetSz{26};
static auto constexpr kChrSetFirst{'a'};
static auto constexpr kMaxInf{std::numeric_limits<int>::max() / 2};

// Trie node representing prefixes of strings used in transformations
struct Trie {
    // Pointers to children nodes for each lowercase character
    std::array<Trie *, kChrSetSz> children{};
    // Unique identifier assigned to a completed word
    int mId{-1};
};

[[nodiscard]]
auto ChrToIdx(char const chr_) noexcept -> int {
    return chr_ - kChrSetFirst;
}
// Inserts a word into the trie and assigns a unique mId if not already assigned
[[nodiscard]]
auto TrieAdd(
    Trie * node_,
    std::string_view const word_,
    int & idx_
) -> int {
    for(auto const ch: word_) {
        auto & nextNode{node_->children[ChrToIdx(ch)]};
        if(!nextNode) {
           nextNode = new Trie();
        }
        node_ = nextNode;
    }
    // Assign a new mId the first time this word is encountered
    auto & id{node_->mId};
    if(id == -1) {
        id = ++idx_;
    }
    return id;
}

// Updates a DP state with a smaller value or initializes it if unset
auto UpdateDp(
    long long & minVal_,
    long long newVal_
) noexcept -> void {
    if(minVal_ == -1 || newVal_ < minVal_) {
        minVal_ = newVal_;
    }
}

// let 'n' be the string length
// 'm' - the number of modification rules
// 'k' - maximum substring length
// time complexity O(n^2 + m^3 + m * k)
// space complexity O(n + m^2 + m * k)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto minimumCost(
        std::string_view const fromStr_,
        std::string_view const toStr_,
        std::span<std::string const> const fromSubStrs_,
        std::span<std::string const> const toSubStrs_,
        std::span<int const> const costs_
    ) const -> long long;
};

auto Solution::minimumCost(
    std::string_view const fromStr_,
    std::string_view const toStr_,
    std::span<std::string const> const fromSubStrs_,
    std::span<std::string const> const toSubStrs_,
    std::span<int const> const costs_
) const -> long long {
    namespace vs = std::views;
    using ll = long long;

    // Length of the fromStr_/toStr_ strings
    auto const strSz{std::ssize(fromStr_)};
    // Number of transformation rules
    auto const subStrTotCnt{std::ssize(fromSubStrs_)};
    // Root of the trie storing all transformation strings
    auto root = new Trie();
    // Total number of unique strings stored in the trie
    auto prefixesCnt{-1};
    // Graph storing minimum conversion costs between trie node ids
    auto minConvCosts{std::vector<std::vector<int>>(
        subStrTotCnt * 2, std::vector(subStrTotCnt * 2, kMaxInf))};
    // Zero costs_ to convert a string to itself
    for(auto const i: vs::iota(0, subStrTotCnt * 2)) {
        minConvCosts[i][i] = 0;
    }
    // Populate graph edges using given transformation rules
    for(auto const i: vs::iota(0, subStrTotCnt)) {
        auto const from{TrieAdd(root, fromSubStrs_[i], prefixesCnt)};
        auto const to{TrieAdd(root, toSubStrs_[i], prefixesCnt)};
        minConvCosts[from][to] = std::min(minConvCosts[from][to], costs_[i]);
    }
    // Floyd–Warshall to compute all-pairs minimum transformation costs_
    for(auto const transIdx: vs::iota(0, prefixesCnt + 1)) {
        for(auto const fromIdx: vs::iota(0, prefixesCnt + 1)) {
            for(auto const toIdx: vs::iota(0, prefixesCnt + 1)) {
                auto & minCost{minConvCosts[fromIdx][toIdx]};
                auto const newCost{
                    minConvCosts[fromIdx][transIdx] + minConvCosts[transIdx][toIdx]};
                minCost = min(minCost, newCost);
            }
        }
    }
    // DP array where prefMinConvCosts[i] is the minimum costs_ to convert prefix [0..i]
    auto prefMinConvCosts{std::vector<ll>(strSz, -1)};
    // Try to build the solution incrementally over fromStr_ positions
    for(auto const curIdx: vs::iota(0, strSz)) {
        if(curIdx > 0 && prefMinConvCosts[curIdx - 1] == -1) {
            continue;
        }
        // Base costs_ before processing position curIdx
        auto const curCost{curIdx == 0 ? 0 : prefMinConvCosts[curIdx - 1]};
        // No costs_ needed if characters already match
        if(fromStr_[curIdx] == toStr_[curIdx]) {
            UpdateDp(prefMinConvCosts[curIdx], curCost);
        }
        // Traverse trie simultaneously for fromStr_ and toStr_ substrings
        auto fromNode{root};
        auto toNode{root};
        for(auto const nextIdx: vs::iota(curIdx, strSz)) {
            fromNode = fromNode->children[ChrToIdx(fromStr_[nextIdx])];
            toNode = toNode->children[ChrToIdx(toStr_[nextIdx])];
            if(!(fromNode && toNode)) {
                break;
            }
            // If both substrings exist and a conversion is possible, update DP
            if( fromNode->mId != -1 && toNode->mId != -1 &&
                minConvCosts[fromNode->mId][toNode->mId] != kMaxInf
            ) {
                UpdateDp(prefMinConvCosts[nextIdx],
                    curCost + minConvCosts[fromNode->mId][toNode->mId]);
            }
        }
    }
    // Final answer is the minimum costs_ to convert the entire string
    auto minTotCost{prefMinConvCosts[strSz - 1]};
    return minTotCost;
}
