// problem : https://leetcode.com/problems/copy-list-with-random-pointer/description/
// submission : https://leetcode.com/problems/copy-list-with-random-pointer/submissions/1534048207
// solution post : https://leetcode.com/problems/copy-list-with-random-pointer/solutions/6386731/c-modern-readable-code-beats-91-runtime-85mhn

// #include <limit>
// #include <vector>
// #include <unordered_map>

namespace Utility {
    auto constexpr dummySzt{std::numeric_limits<size_t>::max()};
}

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

// let 'n' be a length of the given list
// time complexity O(n)
// space complexity O(n)
// runtime 3 ms, beats 91.25 %
/*
class Solution {
public:
    using NodeP = Node *;
    using NodeCP = Node const *;
    NodeP copyRandomList(NodeCP const head) const {
        using namespace Utility;
        if(!head) {
            return nullptr;
        } 
        auto nodeAddrToNodeIdx{CreateNodeAddrToNodeIdx(head)};
        auto nodeIdxToRndNodeIdx{CreateNodeIdxToRndNodeIdx(head,
            nodeAddrToNodeIdx)};
        auto nodeCopyIdxToNodeCopyAddr{std::vector<NodeP>(
            nodeAddrToNodeIdx.size(), nullptr)};
        auto headCopy{CreateCopyLinkedListAndNodeCopyIdxToNodeCopyAddr(
            nodeCopyIdxToNodeCopyAddr, head)};
        SetRandomPointersInCopiedList(headCopy, nodeIdxToRndNodeIdx,
            nodeCopyIdxToNodeCopyAddr);
        return headCopy;
    }
private:
    std::unordered_map<NodeCP, size_t> CreateNodeAddrToNodeIdx(
        NodeCP const head
    ) const {
        auto nodeAddrToNodeIdx{std::unordered_map<NodeCP, size_t>{}};
        auto nodeCurr{head};
        auto nodeIdx{size_t{0}};
        while(nodeCurr) {
           nodeAddrToNodeIdx[nodeCurr] = nodeIdx++;
           nodeCurr = nodeCurr->next;
        }
        return nodeAddrToNodeIdx;
    }
    std::vector<size_t> CreateNodeIdxToRndNodeIdx(
        NodeCP const head,
        std::unordered_map<NodeCP, size_t> const & nodeAddrToNodeIdx
    ) const {
        using namespace Utility;
        auto nodeIdxToRndNodeIdx{std::vector<size_t>(nodeAddrToNodeIdx.size(),
            dummySzt)};
        auto nodeCurr{head};
        auto nodeIdx{size_t{0}};
        while(nodeCurr) {
            if(nodeCurr->random) {
                nodeIdxToRndNodeIdx.at(nodeIdx) = nodeAddrToNodeIdx.at(
                    nodeCurr->random);
            }
            ++nodeIdx;
            nodeCurr = nodeCurr->next;
        }
        return nodeIdxToRndNodeIdx;
    }
    NodeP const CreateCopyLinkedListAndNodeCopyIdxToNodeCopyAddr(
        std::vector<NodeP> & nodeCopyIdxToNodeCopyAddr,
        NodeCP const head
    ) const {
        auto headCopy{static_cast<NodeP const>(new Node{head->val})};
        auto nodeIdx{size_t{0}};
        auto nodeCurr{head};
        auto nodeCurrCopy{headCopy};
        while(nodeCurr) {
            nodeCopyIdxToNodeCopyAddr.at(nodeIdx++) = nodeCurrCopy;
            if(!nodeCurr->next) {
                break;
            }
            nodeCurrCopy->next = new Node{nodeCurr->next->val};    
            nodeCurrCopy = nodeCurrCopy->next;
            nodeCurr = nodeCurr->next;
        }
        return headCopy;
    }
    void SetRandomPointersInCopiedList(
        NodeP const headCopy,
        std::vector<size_t> const & nodeIdxToRndNodeIdx,
        std::vector<NodeP> const & nodeCopyIdxToNodeCopyAddr

    ) const {
        using namespace Utility;
        auto nodeCurrCopy{headCopy};
        auto nodeIdx{size_t{0}};
        while(nodeCurrCopy) {
            if(nodeIdxToRndNodeIdx.at(nodeIdx) != dummySzt) {
                nodeCurrCopy->random = nodeCopyIdxToNodeCopyAddr.at(
                    nodeIdxToRndNodeIdx.at(nodeIdx)); 
            }    
            ++nodeIdx;
            nodeCurrCopy = nodeCurrCopy->next;
        }
    }
};
