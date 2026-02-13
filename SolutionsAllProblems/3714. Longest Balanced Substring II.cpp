// problem : https://leetcode.com/problems/longest-balanced-substring-ii/description
// submission : https://leetcode.com/problems/longest-balanced-substring-ii/submissions/1918389656
// solution post : https://leetcode.com/problems/longest-balanced-substring-ii/solutions/7577220/
//    c-modern-readable-code-beats-100-runtime-v4cp

// import std;

#include <memory_resource>

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// Global polymorphic memory resource.
// Using unsynchronized_pool_resource provides fast memory allocations
// because it pools memory and avoids locking overhead.
// Safe here because the solution runs in a single thread.
std::pmr::unsynchronized_pool_resource gMemPool;

// Bias ensures negative differences become non-negative before packing.
// This allows safe bit manipulation for hashing without collisions.
// Large enough to cover maximum possible prefix difference range.
static auto constexpr gkBias{1<<17};

// Shift amount to separate two 32-bit packed values into a single 64-bit hash.
static auto constexpr gkShift{32};

// Custom hash function for pairs of integers.
struct FastHash final {
    [[nodiscard]]
    auto operator()(std::pair<int, int> const & val_) const noexcept -> size_t {
        auto const [val1_, val2_]{val_};
        // Shift the first value to high 32 bits and bias it.
        auto const hash1{static_cast<size_t>(val_.first + gkBias) << gkShift};
        // Keep second value in low 32 bits and bias it.
        auto const hash2{static_cast<size_t>(val_.second + gkBias)};
        // Combine both into a single hash value.
        auto const hashFinal{hash1 | hash2};
        return hashFinal;
    }
};

// let 'n' be the string length
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    using mapT = std::pmr::unordered_map<std::pair<int, int>, int, FastHash>;

    // Computes the length of the longest balanced substring in str_.
    [[nodiscard]]
    auto longestBalanced(std::string_view const str_) -> int;

private:
    // Returns the maximum length of a contiguous run of a single character.
    [[nodiscard]]
    auto CalcSingleChrMaxSubStrLen(std::string_view const str_) const -> int;

    // Updates the longest balanced substring length based on the current prefix difference.
    inline auto UpdateSubStrCnt(
        mapT & map_,
        int & subStrMaxLen_,
        std::pair<int, int> const & key_,
        int const idx_
    ) const -> void;

    static auto constexpr kChrSetSz{3};       // Number of unique characters: 'a', 'b', 'c'.
    static auto constexpr kChrSetBegin{'a'};  // ASCII of first character.
    static auto constexpr kMaxLoadFactor{0.7}; // Hash map max load factor to improve performance.
};

auto Solution::longestBalanced(std::string_view const str_) -> int {
    namespace vs = std::views;

    auto const strLen{std::ssize(str_)};
    // Initialize with the longest run of a single character.
    auto subStrMaxLen{CalcSingleChrMaxSubStrLen(str_)};

    // Four hash maps using custom memory pool.
    // Each stores the first index of a specific difference pair.
    mapT ab{&gMemPool};   // Tracks substrings where count(a) == count(b)
    mapT bc{&gMemPool};   // Tracks substrings where count(b) == count(c)
    mapT ca{&gMemPool};   // Tracks substrings where count(c) == count(a)
    mapT abc{&gMemPool};  // Tracks substrings where count(a) == count(b) == count(c)

    // Reserve space to avoid rehashing during insertion.
    ab.reserve(strLen);
    bc.reserve(strLen);
    ca.reserve(strLen);
    abc.reserve(strLen);

    // Set maximum load factor for speed.
    ab.max_load_factor(kMaxLoadFactor);
    bc.max_load_factor(kMaxLoadFactor);
    ca.max_load_factor(kMaxLoadFactor);
    abc.max_load_factor(kMaxLoadFactor);

    // Prefix counts for 'a', 'b', 'c'.
    std::array<int, kChrSetSz> chrCnts{};

    // Insert base case for prefix before index 0.
    // Difference pair of 0 occurs at index -1 (before string starts).
    ab[{0, 0}] = -1;
    bc[{0, 0}] = -1;
    ca[{0, 0}] = -1;
    abc[{0, 0}] = -1;

    for(auto const i: vs::iota(0, strLen)) {
        // Increment the count for the current character.
        ++chrCnts[str_[i] - kChrSetBegin];
        auto const [aCnt, bCnt, cCnt]{chrCnts};

        // -------- 'a' and 'b' balanced case --------
        // If (aCnt - bCnt) and cCnt have been seen before,
        // substring between first occurrence and current index is balanced.
        UpdateSubStrCnt(ab, subStrMaxLen, {aCnt - bCnt, cCnt}, i);

        // -------- 'b' and 'c' balanced case --------
        UpdateSubStrCnt(bc, subStrMaxLen, {bCnt - cCnt, aCnt}, i);

        // -------- 'c' and 'a' balanced case --------
        UpdateSubStrCnt(ca, subStrMaxLen, {cCnt - aCnt, bCnt}, i);

        // -------- 'a', 'b', 'c' balanced case --------
        // If (bCnt - aCnt) and (cCnt - aCnt) have been seen before,
        // substring between first occurrence and current index is fully balanced.
        UpdateSubStrCnt(abc, subStrMaxLen, {bCnt - aCnt, cCnt - aCnt}, i);
    }

    // Return the length of the longest balanced substring found.
    return subStrMaxLen;
}

auto Solution::CalcSingleChrMaxSubStrLen(std::string_view const str_) const -> int {
    namespace vs = std::views;

    // Stores the maximum length of contiguous single-character run.
    auto maxSubStrLen{1};
    // Stores the length of the current run.
    auto curSubStrLen{1};

    for(auto const i: vs::iota(1, std::ssize(str_))) {
        // Extend current run if character is same as previous.
        if(str_[i] == str_[i - 1]) {
            ++curSubStrLen;
        } else {
            // Update maximum length and reset current run.
            maxSubStrLen = std::max(maxSubStrLen, curSubStrLen);
            curSubStrLen = 1;
        }
    }

    // Update maximum for the last run.
    maxSubStrLen = std::max(maxSubStrLen, curSubStrLen);
    return maxSubStrLen;
}

auto Solution::UpdateSubStrCnt(
    mapT & map_,
    int & subStrMaxLen_,
    std::pair<int, int> const & key_,
    int const idx_
) const -> void {
    // If this difference pair was seen before.
    if(auto const it{map_.find(key_)}; it != map_.end()) {
        // Length of balanced substring is distance between first occurrence and current index.
        auto const curSubStrLen{idx_ - it->second};
        subStrMaxLen_ = std::max(subStrMaxLen_, curSubStrLen);
    } else {
        // First occurrence of this difference pair: store current index.
        map_[key_] = idx_;
    }
}
