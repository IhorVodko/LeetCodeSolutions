// problem : https://leetcode.com/problems/rotate-list/description/
// submission : https://leetcode.com/problems/rotate-list/submissions/1995792904
// solution post : https://leetcode.com/problems/rotate-list/solutions/6390016/c-modern-readable-code-beats-100-runtime-8vt3

// Approach : Circular Linked List Formation and Break
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the list length
// complexity :  O(n)
// complexity : O(1)

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

class Solution {
public:
    using nodeP = ListNode *;

    [[nodiscard]]
    auto rotateRight(
        nodeP const head_,
        int const offset_
    ) const -> nodeP;
};

Solution::nodeP Solution::rotateRight(
    nodeP const head_,
    int const offset_
) const {
    if(!(head_ && head_->next) || offset_ == 0) {
        return head_;
    }
    // Pointer to find the original tail node
    auto oldTail{head_};
    auto len{1};

    // Traverse until the last node is reached
    while(oldTail->next) {
        ++len;
        oldTail = oldTail->next;
    }

    // If the effective rotation is zero, no changes are needed
    if(offset_ % len == 0) {
        return head_;
    }

    // Connect the original tail to the head, creating a circular list
    oldTail->next = head_;

    // Pointer to find the tail of the newly rotated list
    auto newTail{head_};

    // Calculate the number of steps required to reach the new tail
    len -= (offset_ % len) + 1;

    // Locate the new tail node
    while(--len >= 0) {
        newTail = newTail->next;
    }

    // Identify the new head, which is just after the new tail
    auto const newHead{newTail->next};
    
    // Break the circle to finalize the rotated linked list
    newTail->next = nullptr;

    return newHead;
}
