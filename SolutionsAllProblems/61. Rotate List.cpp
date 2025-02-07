// problem : https://leetcode.com/problems/rotate-list/description/
// submission : https://leetcode.com/problems/rotate-list/submissions/1534891849
// solution post : https://leetcode.com/problems/rotate-list/solutions/6390016/c-modern-readable-code-beats-100-runtime-8vt3

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

// let 'n' be the given list length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    ListNode * rotateRight(
        ListNode * const head,
        int shiftSteps
    ) const {
        if(!(head && head->next)) {
            return head;
        }
        auto oldTail{head};
        auto nodesCount{size_t{1}};
        while(oldTail->next) {
            ++nodesCount;
            oldTail = oldTail->next;
        }
        std::cout << "nodesCount " << nodesCount << '\n';
        oldTail->next = head;
        auto newTail{head};
        nodesCount -= (shiftSteps % nodesCount) + 1;
        while(--nodesCount + 1 >= 1) {
            newTail = newTail->next;
        }
        auto const newHead{newTail->next};
        newTail->next = nullptr;
        return newHead;
    }
};
