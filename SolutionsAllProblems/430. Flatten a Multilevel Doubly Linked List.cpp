// problem : https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/description/
// submission : https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/submissions/1532617125
// solution post : https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/solutions/6381080/c-modern-readable-code-beats-100-runtime-ai21

// #include <stack>

// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

// let 'n' be a length of the given list
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
/*
class Solution {
public:
    Node * flatten(Node * head) const {
        if(!head) {
            return head;
        }
        auto pseudoHead{Node{0, nullptr, head, nullptr}};
        auto curr{static_cast<Node *>(nullptr)};
        auto prev{static_cast<Node *>(&pseudoHead)};
        auto stack{std::stack<Node *>{}};
        stack.push(head);
        while(!stack.empty()) {
            curr = stack.top();
            stack.pop();
            prev->next = curr;
            curr->prev = prev;
            if(curr->next) {
                stack.push(curr->next);
            }
            if(curr->child) {
                stack.push(curr->child);
                curr->child = nullptr;
            }
            prev = curr;
        }
        head->prev = nullptr;
        return head;
    }
};
