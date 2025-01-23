// problem : https://leetcode.com/problems/linked-list-cycle-ii/description/
// submission : https://leetcode.com/problems/linked-list-cycle-ii/submissions/1517815268
// solution post : https://leetcode.com/problems/linked-list-cycle-ii/solutions/6319168/c-modern-readable-code-optimal-time-comp-zmke

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// let 'n' be the given list length
// time complexity O(n)
// space complexity O(1)
// runtime 5 ms, beats 83.30 %

class Solution {
public:
    ListNode * detectCycle(ListNode const * const head) const {
        if(!head) {
            return const_cast<ListNode *>(head); 
        }
        auto slow{head};
        auto fast{head};
        do{
            if(!fast || !fast->next) {
                return nullptr;
            }
            slow = slow->next;
            fast = fast->next->next;
        } while(slow != fast);
        auto slow2{head};
        while(slow2 != slow) {
            slow2 = slow2->next;
            slow = slow->next;
        }
        return const_cast<ListNode *>(slow); 
    }
};
