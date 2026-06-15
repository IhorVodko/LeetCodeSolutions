// problem : https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/description
// submission : https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/submissions/2034148648
// solution post : https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/solutions/8335995/
//    c-modern-readable-code-beats-100-runtime-kbf6

// Approach : Fast and Slow Pointers (Tortoise and Hare)
// Runtime : 0 ms, beats 100.00 %


// Complexity
// let 'n' be the list length
// Time :  O(n)
// Space : O(1)

// import std;

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

class Solution final {
public:
    [[nodiscard]]
    static auto deleteMiddle(ListNode * head) -> ListNode *;
};

auto Solution::deleteMiddle(ListNode * head) -> ListNode * {
    namespace vs = std::views;

    // Handle single node edgecase
    if(!head->next) {
        return nullptr;
    }

    auto slow{head};
    // Offset fast to ensure slow stops exactly one node before the middle
    auto fast{head->next->next};
    
    while(fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }

    // delete middle node at index floor(n / 2)
    slow->next = slow->next->next;

    return head;
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
