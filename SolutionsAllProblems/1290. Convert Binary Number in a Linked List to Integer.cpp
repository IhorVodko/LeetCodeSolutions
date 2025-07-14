// problem : https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/description/
// submission : https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/submissions/1697631278
// solution post : https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/solutions/6958063/
//    c-modern-readable-code-beats-100-runtime-cmr5

// #include <bitset>

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
namespace Util {
    inline auto constexpr kBinSzMax{30};
}

class Solution {
public:
    using NodeConstT = ListNode const *;
// let 'n' be a length of the given list
// time complexity O(n)
// space complexity O(l)
// runtime 0 ms, beats 100.00 %
    int getDecimalValue(NodeConstT const head_);
private:
    std::bitset<Util::kBinSzMax> mNumBin;
};

int Solution::getDecimalValue(NodeConstT const head_) {
    using namespace Util;
    mNumBin.reset();
    for(auto node{head_}; node; node = node->next) {
        mNumBin <<= 1;
        mNumBin.set(0, node->val == 1);
    }
    auto const numDec{mNumBin.to_ulong()};
    return numDec;
}
