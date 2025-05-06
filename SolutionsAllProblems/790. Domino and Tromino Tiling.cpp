// problem : https://leetcode.com/problems/domino-and-tromino-tiling/description/
// submission : https://leetcode.com/problems/domino-and-tromino-tiling/submissions/1627088245
// solution post : https://leetcode.com/problems/domino-and-tromino-tiling/solutions/6720574/
//    c-modern-readable-code-beats-100-runtime-2ux7

namespace Utility {
    auto constexpr kMod{static_cast<int>(1e9) + 7};
}

class Solution {
public:
// let 'n' be a length of the given board
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    int numTilings(int const boardLength_) const;
};

int Solution::numTilings(int const boardLength_) const {
    using namespace Utility;
    if(boardLength_ <= 2) {
        return boardLength_;
    }
    auto fullCoveredTilesCurr{5l};
    auto fullCoveredTilesPrev{2l};
    auto fullCoveredTilesBeforePrev{1l};
    for(auto idx{4}; idx < boardLength_ + 1; ++idx) {
        auto tmp{fullCoveredTilesPrev};
        fullCoveredTilesPrev = fullCoveredTilesCurr;
        fullCoveredTilesCurr = (2 * fullCoveredTilesCurr + fullCoveredTilesBeforePrev) % kMod;
        fullCoveredTilesBeforePrev = tmp;
    }
    return static_cast<int>(fullCoveredTilesCurr); 
}
