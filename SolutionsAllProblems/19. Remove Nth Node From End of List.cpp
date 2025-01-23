// problem : https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/ 
// submission : https://leetcode.com/problems/remove-nth-node-from-end-of-list/submissions/1517956441
// solution post : https://leetcode.com/problems/remove-nth-node-from-end-of-list/solutions/6319865/c-modern-readable-code-beats-100-runtime-j4zk

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

// let 'n' be length of the given list 
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using NodeP = ListNode *;
    NodeP removeNthFromEnd(
        NodeP const head,
        int const nth
    ) const {
        auto  preHead{ListNode{-1}};
        preHead.next = head;
        auto first{&preHead};
        auto second{&preHead};
        for(auto i{size_t{0}}; i <= nth; ++i) {
            second = second->next;
        }
        while(second) {
            first = first->next;
            second = second->next;
        }
        first->next = first->next->next;
        return preHead.next; 
    }
};
