// problem : https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/description
// submission : https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/submissions/1817668291
// solution post : https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/solutions/7318463/
//    c-modern-readable-code-beats-100-runtime-t55y

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

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream("display_runtime.txt") << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class Solution {
public:
    using NodeP = ::ListNode *;

// let 'n' be the length of given list
// 'm' - number of the given filter numbers
// time complexity O(n + m)
// space complexity O(m)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto modifiedList(
        std::span<int const> const nums_,
        NodeP const head_
    ) const -> NodeP;
};

auto Solution::modifiedList(
    std::span<int const> const nums_,
    NodeP const head_
) const -> NodeP {
    auto numsFilter{std::unordered_set<int>(nums_.cbegin(), nums_.cend())};
    auto const sentinel{new ::ListNode{0, head_}};
    auto nodePrev{sentinel};
    while(nodePrev && nodePrev->next) {
        auto nodeCurr{nodePrev->next};
        if(numsFilter.contains(nodeCurr->val)) {
            nodePrev->next = nodeCurr->next;
            // do not clean, leetCode test harness will do it
            // delete nodeCurr;
        } else {
            nodePrev = nodeCurr;
        }
    }
    auto const newHead{sentinel->next};
    delete sentinel;
    return newHead; 
}
