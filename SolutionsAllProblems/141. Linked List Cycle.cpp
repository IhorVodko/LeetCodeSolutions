// problem : https://leetcode.com/problems/linked-list-cycle/description/
// submission : https://leetcode.com/problems/linked-list-cycle/submissions/1517778645
// solution post : https://leetcode.com/problems/linked-list-cycle/solutions/6318991/c-modern-readable-code-beats-91-runtime-nyvvn

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// let 'n' be a length of the given list
// time complexity O(n)
// space complexity O(1)
// runtime 6 ms, beats 90.70 %

class Solution {
public:
    bool hasCycle(ListNode const * const head) const {
        if(!head) {
            return false;
        }
        auto slow{head};
        auto fast{head->next}; 
        while(slow != fast) {
            if(!fast || !fast->next) {
                return false;
            }
            slow = slow->next;
            fast = fast->next->next;
        }
        return true;
    }
};
