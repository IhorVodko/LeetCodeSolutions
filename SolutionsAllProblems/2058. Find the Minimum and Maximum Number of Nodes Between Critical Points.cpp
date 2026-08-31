// problem : https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/description
// submission : https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/submissions/2126298336
// solution post : https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/solutions/8493723/
//    simplanation-simple-explanation-by-cyber-hcn4

// Approach : One-Pass Sliding Window State Tracking
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the number of list nodes
// Time :  O(n)
// Space : O(1)

// import std;

// #include <algorithm>
// #include <iostream>
// #include <limits>
// #include <utility>
// #include <vector>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

namespace {

constexpr auto kNotFoundVal{-1};
constexpr auto kUninitIdx{-1};
constexpr auto kStartIdx{1};
constexpr auto kDistUpLim{std::numeric_limits<int>::max()};

constexpr auto hasInsufficientNodes{[] [[nodiscard]] (auto const headNode_) static {
    return !headNode_ || !headNode_->next || !headNode_->next->next;
}};

constexpr auto isCriticalPoint{[] [[nodiscard]] (
    auto const prevVal_,
    auto const currVal_,
    auto const nextVal_
) static {
    return
        (currVal_ < prevVal_ && currVal_ < nextVal_) ||
        (currVal_ > prevVal_ && currVal_ > nextVal_)
    ;
}};

// Initializer to configure fast I/O before main() runs
[[maybe_unused]]
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace 

class Solution final {
public:
    using NodeP = ListNode const *;

    [[nodiscard]]
    static auto nodesBetweenCriticalPoints(NodeP const headNode_) -> std::vector<int>;
};

auto Solution::nodesBetweenCriticalPoints(NodeP const headNode_) -> std::vector<int> {
    // 1. Guard against lists too short to form any critical points
    if(hasInsufficientNodes(headNode_)) {
        return {kNotFoundVal, kNotFoundVal};
    }

    // 2. Initialize sliding window of three nodes for local extrema detection
    auto prevNode{headNode_};
    auto currNode{prevNode->next};
    auto nextNode{currNode->next};

    // 3. Track position indices to calculate distances lazily
    auto firstIdx{kUninitIdx};
    auto lastIdx{kUninitIdx};
    auto currIdx{kStartIdx};

    auto minDist{kDistUpLim};

    // 4. Traverse the list evaluating every contiguous triplet
    while(nextNode) {
        // 5. Process discovered local maximum or minimum
        if(isCriticalPoint(prevNode->val, currNode->val, nextNode->val)) {
            if(firstIdx == kUninitIdx) {
                // Record the initial anchor point to establish max possible distance
                firstIdx = currIdx;
            } else {
                // Compute local minimum distance using adjacent critical points
                minDist = std::min(minDist, currIdx - lastIdx);
            }
            // Update reference point for the next potential minimum distance check
            lastIdx = currIdx; 
        }

        // Advance the three-node sliding window
        prevNode = std::exchange(currNode, nextNode);
        nextNode = nextNode->next;

        ++currIdx;
    }

    // 6. Handle edge cases where fewer than two critical points exist
    if(minDist == kDistUpLim) {
        return {kNotFoundVal, kNotFoundVal};
    }

    // 7. Calculate global maximum distance using outer boundaries
    auto const maxDist{lastIdx - firstIdx};

    return {minDist, maxDist};
}
