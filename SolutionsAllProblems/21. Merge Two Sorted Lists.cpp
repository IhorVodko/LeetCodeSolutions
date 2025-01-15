// problem : https://leetcode.com/problems/merge-two-sorted-lists/description/
// submission : https://leetcode.com/problems/merge-two-sorted-lists/submissions/1509431766
// solution post : https://leetcode.com/problems/merge-two-sorted-lists/solutions/6284416/c-modern-readable-code-beats-100-runtime-dgyr

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

// let 'l1' be a nodes count of parameter 'list1'
// 'l2' - nodes count of parameter 'list2'
// time complexity O(l1 + l2)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %

class Solution {
public:
    ListNode * mergeTwoLists(
        ListNode * list1,
        ListNode * list2
    ) const {
        auto preHead{ListNode{-101}};
        auto prevNode{&preHead};
        while(list1 && list2) {
            if(list1->val <= list2->val) {
                prevNode->next = list1;
                list1 = list1->next;
            } else {
                prevNode->next = list2;
                list2 = list2->next;
            }
            prevNode = prevNode->next;
        }
        prevNode->next = list1 ? list1 : list2;
        return preHead.next;
    }
};
