// problem : https://leetcode.com/problems/insert-into-a-sorted-circular-linked-list/description/
// submission : https://leetcode.com/problems/insert-into-a-sorted-circular-linked-list/submissions/1532708459
// solution post : https://leetcode.com/problems/insert-into-a-sorted-circular-linked-list/solutions/6381509/c-modern-readable-code-beats-100-runtime-4vq3

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/

// let 'n' be a length of the given list
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    Node * insert(
        Node * head,
        int const insertVal
    ) const {
        if(!head) {
            head = new Node{insertVal};
            head->next = head;
            return head;
        }
        auto prev{head};
        auto curr{head->next};
        auto isPlaceToInsert{false};
        do{
            if(prev->val <= insertVal && insertVal <= curr->val) {
                isPlaceToInsert = true;
            } else if(prev->val > curr->val) {
                if(prev->val <= insertVal || insertVal <= curr->val) {
                    isPlaceToInsert = true;
                }
            }
            if(isPlaceToInsert) {
                prev->next = new Node{insertVal, curr};
                return head;
            }
            prev = curr;
            curr = curr->next;
        } while(prev != head);
        prev->next = new Node(insertVal, curr);
        return head;
    }
};
