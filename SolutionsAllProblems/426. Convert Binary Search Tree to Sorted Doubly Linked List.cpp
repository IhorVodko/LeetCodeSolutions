// problem : https://leetcode.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/description/
// submission : https://leetcode.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/submissions/
//    1681650648
// solution post : https://leetcode.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/solutions/
//    6903566/c-modern-readable-code-beats-100-runtime-s2rp

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/

class Solution {
public:
    using NodePT = Node *;
// let 'n' be a count of given nodes
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    NodePT treeToDoublyList(NodePT root_);
private:
    void DoInorderDFS(NodePT node_);
    NodePT mNodeFirst{nullptr};
    NodePT mNodeLast{nullptr};
};

Solution::NodePT Solution::treeToDoublyList(NodePT root_) { 
    mNodeFirst = nullptr;
    mNodeLast = nullptr;
    if(!root_) {
        return nullptr;
    }
    DoInorderDFS(root_);
    mNodeLast->right = mNodeFirst;
    mNodeFirst->left = mNodeLast;
    return mNodeFirst;
}

void Solution::DoInorderDFS(NodePT node_) {
    if(!node_) {
        return;
    }
    DoInorderDFS(node_->left);
    if(mNodeLast) {
        mNodeLast->right = node_;
        node_->left = mNodeLast;
    } else {
        mNodeFirst = node_;
    }
    mNodeLast = node_;
    DoInorderDFS(node_->right);
}
