// problem : https://leetcode.com/problems/add-two-numbers/description/
// submission : https://leetcode.com/problems/add-two-numbers/submissions/1531007737
// solution post : https://leetcode.com/problems/add-two-numbers/solutions/6373689/c-modern-readable-code-beats-100-runtime-85bz

namespace Utility {
    auto constexpr base{10};
}

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

// let 'l1' be an input first list length
// 'l2' - second list length
// time complexity O(max(l1, l2))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    ListNode * addTwoNumbers(
        ListNode const * const l1,
        ListNode const * const l2
    ) const {
        auto node1{l1};
        auto node2{l2};
        auto nodeResult{ListNode{-1}};
        auto node{static_cast<ListNode *>(&nodeResult)};
        auto sum{-1};
        auto carry{0}; 
        while(node1 && node2) {
            DoSum(carry, node1->val + node2->val + carry, node);
            node1 = node1->next;
            node2 = node2->next;
        } 
        node1 = node1 ? node1 : node2;
        while(node1) {
            DoSum(carry, node1->val + carry, node);
            node1 = node1->next;
        }
        if(carry == 1) {
            node->next = new ListNode{carry};
        }
        return nodeResult.next;
    }
private:
    void DoSum(
        int & carry,
        int const sum,
        ListNode * & node
    ) const {
        using namespace Utility;
        carry = sum / base;
        node->next = new ListNode{sum % base};
        node = node->next;
    }
};
