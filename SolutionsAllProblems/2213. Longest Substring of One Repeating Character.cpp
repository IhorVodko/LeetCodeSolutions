// problem : https://leetcode.com/problems/longest-substring-of-one-repeating-character/description
// submission : https://leetcode.com/problems/longest-substring-of-one-repeating-character/submissions/2105865086
// solution post : https://leetcode.com/problems/longest-substring-of-one-repeating-character/solutions/8459360/
//    simplanation-simple-explanation-by-cyber-jill

// Approach : Segment Tree for Dynamic Range Queries
// Runtime : 105 ms, beats 98.66 %

// Complexity analysis
// let 'n' be the string length
// 'm' - number of queries
// Time :  O(n + m * log(n))
// Space : O(n)

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// Holds repeating character sequence metrics for a specific text range
struct SegmentNode {
    // Longest identical character sequence overall
    int maxStreak{0};
    // Longest sequence starting from the left boundary
    int prefStreak{0};
    // Longest sequence ending at the right boundary
    int sufStreak{0};
};

// Dynamically tracks the longest repeating character substrings
class ChrSegmentTree final {
public:
    // 1. Initialize segment tree and allocate nodes
    explicit ChrSegmentTree(std::string textContent_) :
        mCurrTxt{std::move(textContent_)},
        mTxtLen{static_cast<int>(mCurrTxt.length())}
    {

        mTreeNodes.assign(4 * mTxtLen + 1, SegmentNode{});
        if(mTxtLen > 0) {
            buildTree(1, 0, mTxtLen - 1);
        }
    }

    [[nodiscard]]
    auto processQuery(
        int const targetIndex_,
        char const newCharacter_
    ) -> int {
        // Update character and propagate tree changes
        mCurrTxt[targetIndex_] = newCharacter_;
        updateTree(1, 0, mTxtLen - 1, targetIndex_);

        return mTreeNodes[1].maxStreak;
    }

private:
    [[nodiscard]]
    // 2. Combine child nodes to compute parent properties
    auto mergeSegments(
        SegmentNode const& leftNode_,
        SegmentNode const& rightNode_,
        int const leftSize_,
        int const rightSize_,
        bool const charactersMatch_
    ) const -> SegmentNode {

        auto combinedNode{SegmentNode{}};

        // Base max is the highest from either child
        combinedNode.maxStreak = std::max(
            leftNode_.maxStreak, rightNode_.maxStreak);

        // Bridge max streak across boundary if characters match
        if(charactersMatch_) {
            combinedNode.maxStreak = std::max(
                combinedNode.maxStreak,
                leftNode_.sufStreak + rightNode_.prefStreak);
        }

        // Inherit left prefix, extend if it spans entire left segment
        combinedNode.prefStreak = leftNode_.prefStreak;
        if(charactersMatch_ && leftNode_.prefStreak == leftSize_) {
            combinedNode.prefStreak += rightNode_.prefStreak;
        }

        // Inherit right suffix, extend if it spans entire right segment
        combinedNode.sufStreak = rightNode_.sufStreak;
        if(charactersMatch_ && rightNode_.sufStreak == rightSize_) {
            combinedNode.sufStreak += leftNode_.sufStreak;
        }

        return combinedNode;
    }

    // 3. Recursively construct the segment tree
    auto buildTree(
        int const currentNode_, 
        int const rangeStart_, 
        int const rangeEnd_
    ) -> void {

        // Leaf nodes inherently have streaks of exactly one
        if(rangeStart_ == rangeEnd_) {
            mTreeNodes[currentNode_] = {1, 1, 1};
            return;
        }

        // Split current range into left and right halves
        auto const middlePoint{rangeStart_ + (rangeEnd_ - rangeStart_) / 2};
        auto const leftChildIndex{2 * currentNode_};
        auto const rightChildIndex{2 * currentNode_ + 1};

        // Recursively construct child branches
        buildTree(leftChildIndex, rangeStart_, middlePoint);
        buildTree(rightChildIndex, middlePoint + 1, rangeEnd_);

        auto const leftSegmentSize{middlePoint - rangeStart_ + 1};
        auto const rightSegmentSize{rangeEnd_ - middlePoint};
        // Evaluate boundary continuity to merge states
        auto const crossBoundaryMatch{
            mCurrTxt[middlePoint] == mCurrTxt[middlePoint + 1]
        };

        // Aggregate child properties into parent node
        mTreeNodes[currentNode_] = mergeSegments(
            mTreeNodes[leftChildIndex],
            mTreeNodes[rightChildIndex],
            leftSegmentSize,
            rightSegmentSize,
            crossBoundaryMatch
        );
    }

    // 4. Traverse and update tree for modified index
    auto updateTree(
        int const currentNode_,
        int const rangeStart_,
        int const rangeEnd_,
        int const targetIndex_
    ) -> void {

        // Reached target leaf node
        if(rangeStart_ == rangeEnd_) {
            return;
        }

        auto const middlePoint{rangeStart_ + (rangeEnd_ - rangeStart_) / 2};
        auto const leftChildIndex{2 * currentNode_};
        auto const rightChildIndex{2 * currentNode_ + 1};

        // Route update to the segment containing the target index
        if(targetIndex_ <= middlePoint) {
            updateTree(leftChildIndex, rangeStart_, middlePoint, targetIndex_);
        } else {
            updateTree(rightChildIndex, middlePoint + 1, rangeEnd_, targetIndex_);
        }

        auto const leftSegmentSize{middlePoint - rangeStart_ + 1};
        auto const rightSegmentSize{rangeEnd_ - middlePoint};
        // Re-evaluate boundary continuity after character update
        auto const crossBoundaryMatch{
            mCurrTxt[middlePoint] == mCurrTxt[middlePoint + 1]
        };

        // Recompute parent state based on updated children
        mTreeNodes[currentNode_] = mergeSegments(
            mTreeNodes[leftChildIndex],
            mTreeNodes[rightChildIndex],
            leftSegmentSize,
            rightSegmentSize,
            crossBoundaryMatch
        );
    }

    std::vector<SegmentNode> mTreeNodes{};
    std::string mCurrTxt{};
    int mTxtLen{0};
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    static auto longestRepeating(
        std::string textContent_,
        std::string const& queryCharacters_,
        std::vector<int>& queryIndices_
    ) -> std::vector<int>;
};

auto Solution::longestRepeating(
    std::string textContent_,
    std::string const& queryCharacters_,
    std::vector<int>& queryIndices_
) -> std::vector<int> {

    auto segmentTree{ChrSegmentTree{std::move(textContent_)}};

    // 5. Apply sequence of queries and collect results
    auto const applyQuery{[&] (auto const queryPosition_) -> int {
            // Extract query parameters and process update
            auto const newCharacter{queryCharacters_[queryPosition_]};
            auto const targetLocation{queryIndices_[queryPosition_]};

            return segmentTree.processQuery(targetLocation, newCharacter);
        }
    };

    // Map over query indices and evaluate lazily
    return 
        vs::iota(0uz, queryCharacters_.size()) |
        vs::transform(applyQuery) | 
        rs::to<std::vector>()
    ;
}
