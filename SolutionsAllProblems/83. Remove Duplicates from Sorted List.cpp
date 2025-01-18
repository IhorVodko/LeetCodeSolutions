// problem : https://leetcode.com/problems/remove-duplicates-from-sorted-list/editorial/
// submission : https://leetcode.com/problems/remove-duplicates-from-sorted-list/submissions/1512773924
// solution post : https://leetcode.com/problems/remove-duplicates-from-sorted-list/solutions/6299689/c-modern-readable-code-beats-100-runtime-5pg3

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

// let 'n' be a count of nodes in the given list 
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    ListNode * deleteDuplicates(ListNode * head) const {
        auto node{head};
        while(node && node->next) {
            if(node->val == node->next->val) {
                node->next = node->next->next;
            } else {
                node = node->next;
            }
        }
        return head;
    }
};
