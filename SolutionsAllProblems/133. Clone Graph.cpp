// problem : https://leetcode.com/problems/clone-graph/description/
// submission : https://leetcode.com/problems/clone-graph/submissions/1548854103
// solution post : https://leetcode.com/problems/clone-graph/solutions/6443542/
//     c-modern-readable-code-beats-100-runtime-cahc

// #include <unordered_map>

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

// let 'v' be a number of vertices
// 'e' - number of edges
// time complexity O(v + e)
// space complexity O(v)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    Node * cloneGraph(Node * node) {
        nodeToNodeCopy.clear();
        return DoCloneGraph(node);
    }
    Node * DoCloneGraph(Node * node) {
        if(!node) {
            return node;
        }
        if(nodeToNodeCopy.contains(node)) {
            return nodeToNodeCopy.at(node);
        }
        auto nodeCopy{new Node{node->val}};
        nodeToNodeCopy[node] = nodeCopy;
        for(auto neighborNode: node->neighbors) {
            nodeCopy->neighbors.emplace_back(DoCloneGraph(neighborNode));
        }
        return nodeCopy;
    }
private:
    std::unordered_map<Node *, Node *> nodeToNodeCopy;
};
