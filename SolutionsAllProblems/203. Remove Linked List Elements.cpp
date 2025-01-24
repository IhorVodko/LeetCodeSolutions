// problem : https://leetcode.com/problems/remove-linked-list-elements/submissions/1518878084/
// submission : https://leetcode.com/problems/remove-linked-list-elements/submissions/1518878084
// solution post : https://leetcode.com/problems/remove-linked-list-elements/solutions/6323360/c-modern-readable-code-beats-100-runtime-uq5w

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

// let 'n' be a given list 'head' length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %

class Solution {
public:
    using NodeP = ListNode *;
    NodeP removeElements(
        NodeP  const head,
        int const val
    ) const {
        auto preHead{ListNode{-1}};    
        preHead.next = head;
        auto node{&preHead};
        while(node->next) {
            if(node->next->val == val) {
                node->next = node->next->next;
            } else {
                node = node->next;
            }        
        }
        return preHead.next;
    }
};
