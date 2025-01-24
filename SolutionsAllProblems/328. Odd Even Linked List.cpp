// problem : https://leetcode.com/problems/odd-even-linked-list/description/
// submission : https://leetcode.com/problems/odd-even-linked-list/submissions/1518903253
// solution post : https://leetcode.com/problems/odd-even-linked-list/solutions/6323464/c-modern-readable-code-beats-100-runtime-7i3o

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
// runtime 0 ms, beats 100.00
class Solution {
public:
    using NodeP = ListNode *;
    NodeP oddEvenList(NodeP const head) const {
        if(!head || !head->next) {
            return head;
        }
        auto node{head};
        auto preHeadEven{ListNode{numeric_limits<int>::min()}};
        auto nodeEven{&preHeadEven};
        while(node) {
            nodeEven->next = node->next;
            nodeEven = nodeEven->next;
            if(!node->next || !node->next->next) {
                node->next = preHeadEven.next;
                break;
            }
            node->next = node->next->next;
            node = node->next;
        } 
        return head; 
    }
};
