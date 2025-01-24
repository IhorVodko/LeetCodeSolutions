// problem : https://leetcode.com/problems/palindrome-linked-list/description/
// submission : https://leetcode.com/problems/palindrome-linked-list/submissions/1518957027
// solution post : https://leetcode.com/problems/palindrome-linked-list/solutions/6323668/c-modern-readable-code-beats-100-runtime-vr6f

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

// let 'n' be a given list length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using NodeP = ListNode *;
    bool isPalindrome(NodeP const head) const {
        if(!head) {
            return true;
        }
        auto firstHalfEnd{FindEndOfFirstHalf(head)};
        auto secondHalfStart{ReverseList(firstHalfEnd->next)};
        auto p1{head};
        auto p2{secondHalfStart};
        auto result{true};
        while(p2) {
            if(p1->val != p2->val) {
                result = false;
                break;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        firstHalfEnd->next = ReverseList(secondHalfStart);
        return result;
    }
private:
    NodeP ReverseList(NodeP const head) const {
        auto prev{NodeP{nullptr}};
        auto curr{head};
        auto nextTemp{NodeP{nullptr}};
        while(curr) {
            nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }
        return prev;
    }
    NodeP FindEndOfFirstHalf(NodeP const head) const {
        auto fastP{head};
        auto slowP{head};
        while(fastP->next && fastP->next->next) {
            fastP = fastP->next->next;
            slowP = slowP->next;
        }
        return slowP;
    }
};
