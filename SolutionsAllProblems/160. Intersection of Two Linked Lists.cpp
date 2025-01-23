// problem : https://leetcode.com/problems/intersection-of-two-linked-lists/description/ 
// submission : https://leetcode.com/problems/intersection-of-two-linked-lists/submissions/1517845356
// solution post : https://leetcode.com/problems/intersection-of-two-linked-lists/solutions/6319324/c-modern-readable-code-beats-95-runtime-cgzcj

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// let 'a' be the given list 'headA' length
// 'b' - 'headB' length
// time complexity O(a + b)
// space complexity O(1)
// runtime 28 ms, beats 95.35 %

class Solution {
public:
    using NodeP = ListNode *;
    using NodeCP = ListNode const *; 
    NodeP getIntersectionNode(
        NodeCP const headA,
        NodeCP const headB
    ) const {
        auto nodeA{headA};
        auto nodeB{headB};
        while(nodeA != nodeB) {
            nodeA = nodeA == nullptr ? headB : nodeA->next;
            nodeB = nodeB == nullptr ? headA : nodeB->next; 
        } 
        return const_cast<NodeP>(nodeA); 
    }
};
