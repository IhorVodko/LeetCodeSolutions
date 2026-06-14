// problem : https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/description 
// submission : https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/submissions/2033188882
// solution post : https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/solutions/8334224/
//    c-modern-readable-code-beats-100-runtime-nrnq

// Approach : Fast & Slow Pointers with In-Place Reversal
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the list length
// Time :  O(n)
// Space : O(1)

// import std;

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

class Solution final {
public:
    using NodeP = ListNode *;

    [[nodiscard]]
    static auto pairSum(NodeP head_) -> int;
};

auto Solution::pairSum(NodeP head_) -> int {
    auto slow{head_};
    auto fast{head_};
    auto prev{static_cast<NodeP>(nullptr)};

    // Reverse the first half of the linked list while finding its midpoint
    while(fast && fast->next) {
        fast = fast->next->next;

        auto nextNode{slow->next};
        slow->next = prev;
        prev = slow;
        slow = nextNode;
    }

    auto maxSum{0};
    // Traverse from the center outward to calculate twin sums
    while(slow) {
        maxSum = std::max(maxSum, prev->val + slow->val);

        prev = prev->next;
        slow = slow->next;
    }

    return maxSum;
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
