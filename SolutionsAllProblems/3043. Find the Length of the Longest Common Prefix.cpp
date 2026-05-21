// problem : https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/description
// submission : https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/submissions/2009337159
// solution post : https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/solutions/8284856/
//    c-modern-readable-code-beats-100-runtime-9nr0

// Approach : Trie (Prefix Tree) with Arena Allocation
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the length of the shorter array of numbers
// 'm' - length of the longer array of numbers
// 'd' - maximum number of digits in any given number
// complexity :  O((n + m) * d)
// complexity : O(n * d)

// import std;

#include <memory_resource>

namespace {

// Represents a single digit node in the prefix tree structure.
struct PrefixTrieNode final {
    std::array<PrefixTrieNode *, 10> mChildren{};
};

// Prefix tree optimized with arena allocation for fast integer digit storage.
class PrefixTrie final {
public:
    PrefixTrie(
        std::pmr::memory_resource * mem_,
        std::vector<int> const & nums_    
    ):
        alloc{mem_}
    {
        mRoot = alloc.new_object<PrefixTrieNode>();

        // Populate the tree with all available prefixes from the source array.
        for(auto const num: nums_) {
            Insert(num);
        }
    }

    // Decomposes the integer to insert its digits sequentially from left to right.
    auto Insert(int num_) -> const void
    {
        auto node{mRoot};
        auto divisor{1};
        auto tempNum{num_};

        // Determine the magnitude to extract the most significant digit first.
        while(tempNum >= 10) {
            divisor *= 10;
            tempNum /= 10;
        }

        // Traverse downwards, allocating missing digit branches along the way.
        while(divisor > 0) {
            auto digit{num_ / divisor};

            if(!node->mChildren[digit]) {
                auto const child{alloc.new_object<PrefixTrieNode>()};
                node->mChildren[digit] = child;
            }

            node = node->mChildren[digit];
            num_ %= divisor;
            divisor /= 10;
        }
    }

    // Evaluates the depth of the matching digit sequence for the target integer.
    [[nodiscard]]
    auto ComputeLongestCommPref(int num_) const -> int
    {
        auto node{mRoot};
        auto divisor(1);
        auto tempNum{num_};

        // Calculate the divisor needed for left-to-right digit extraction.
        while(tempNum >= 10) {
            divisor *= 10;
            tempNum /= 10;
        }

        auto len{0};

        // Follow the established digit branches until a mismatch occurs.
        while(divisor > 0 && node->mChildren[num_ / divisor]) {
            ++len;

            node = node->mChildren[num_ / divisor];
            num_ %= divisor;
            divisor /= 10;
        }

        return len;
    }

private:
    std::pmr::polymorphic_allocator<PrefixTrieNode> alloc;
    PrefixTrieNode * mRoot;
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto longestCommonPrefix(
        std::vector<int> const & nums1_,
        std::vector<int> const & nums2_
    ) -> int;
};

auto Solution::longestCommonPrefix(
    std::vector<int> const & nums1_,
    std::vector<int> const & nums2_
) -> int
{
    // Ensure the prefix tree is built from the smaller array to minimize memory.
    if(nums1_.size() > nums2_.size()) {
        longestCommonPrefix(nums2_, nums1_);
    }

    // Fast arena allocator prevents overhead from individual node heap allocations.
    auto mem{std::pmr::monotonic_buffer_resource{}};
    auto trie{PrefixTrie{&mem, nums1_}};
    auto maxLen{0};

    // Query each candidate against the tree to track the longest matching sequence.
    for(auto num: nums2_) {
        maxLen = std::max(maxLen, trie.ComputeLongestCommPref(num));
    }

    return maxLen;
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
