// problem : https://leetcode.com/problems/delete-n-nodes-after-m-nodes-of-a-linked-list/description
// submission : https://leetcode.com/problems/delete-n-nodes-after-m-nodes-of-a-linked-list/submissions/1648160717
// solution post : https://leetcode.com/problems/delete-n-nodes-after-m-nodes-of-a-linked-list/solutions/6793464/
//    c-modern-readable-code-beats-100-by-cybe-lqcm

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
class Solution {
public:
    using NodePC = ListNode * const;
// let 'n' be a length of the given list
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    ListNode * deleteNodes(
        NodePC head_,
        int const nodesToSaveCount_,
        int const nodesToDeleteCount_
    ) const;
};

ListNode * Solution::deleteNodes(
    NodePC head_,
    int const nodesToSaveCount_,
    int const nodesToDeleteCount_
) const {
    auto node{head_};
    auto savedNodesCount{1};
    auto deletedNodesCount{1};
    auto isInSavingMode{true};
    while(node) {
        while(node && savedNodesCount < nodesToSaveCount_) {
            ++savedNodesCount;
            node = node->next; 
        }
        savedNodesCount = 1;
        while(node && node->next && deletedNodesCount <= nodesToDeleteCount_) {
            ++deletedNodesCount;
            auto nodeToDelete{node->next}; 
            node->next = node->next->next;
            delete nodeToDelete;
        }
        if(node) {
            node = node->next; 
        }
        deletedNodesCount = 1;
    }
    return const_cast<ListNode *>(head_);
}
