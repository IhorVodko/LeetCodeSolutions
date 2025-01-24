// problem : https://leetcode.com/problems/reverse-linked-list/description/
// submission : https://leetcode.com/problems/reverse-linked-list/submissions/1518865825
// solution post : https://leetcode.com/problems/reverse-linked-list/solutions/6323329/c-modern-readable-code-beats-100-runtime-zlvt

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

// let 'n' be a lenght of the given list 'head'
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using NodeP = ListNode *;
    NodeP reverseList(NodeP const head) const {
        if(!head) {
            return head;
        }
        auto newHead{head};
        auto newAfterHead{head->next};
        while(head->next) {
            newAfterHead = head->next->next;
            head->next->next = newHead;
            newHead = head->next;
            head->next = newAfterHead;
        }
        return newHead;
    }
};
