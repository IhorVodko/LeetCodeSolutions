// problem : https://leetcode.com/problems/swap-nodes-in-pairs/description/ 
// submission : https://leetcode.com/problems/swap-nodes-in-pairs/submissions/1649009780
// solution post : https://leetcode.com/problems/swap-nodes-in-pairs/solutions/6796260/
//    c-modern-readable-code-beats-100-by-cybe-vtnl

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
    using NodePT = ListNode *;
// let 'n' be a length of the given list
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    NodePT swapPairs(NodePT const head_) const;
private:
    void DoSwapPairs(
        NodePT nodePrev_,
        NodePT nodeCurr_
    ) const;
};

Solution::NodePT Solution::swapPairs(NodePT const head_) const{
    auto headNew{(!head_ || !head_->next) ? head_ : head_->next};
    DoSwapPairs(nullptr, head_);
    return headNew;
}

void Solution::DoSwapPairs(
    NodePT nodePrev_,
    NodePT nodeCurr_
) const {
    if(!(nodeCurr_ && nodeCurr_->next)) {
        return;
    }
    auto const nodeCurOld{nodeCurr_};
    auto const nodeNextOld{nodeCurr_->next};
    nodeCurr_->next = nodeNextOld->next;
    nodeNextOld->next = nodeCurOld;
    if(nodePrev_) {
        nodePrev_->next = nodeNextOld;
    }
    DoSwapPairs(nodeCurr_, nodeCurr_->next);
}
