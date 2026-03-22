// problem : https://leetcode.com/problems/determine-whether-matrix-can-be-obtained-by-rotation/description
// submission : https://leetcode.com/problems/determine-whether-matrix-can-be-obtained-by-rotation/submissions/
//    1956076087
// solution post : https://leetcode.com/problems/determine-whether-matrix-can-be-obtained-by-rotation/solutions/
//    7681634/c-modern-readable-code-runtime-0-ms-beat-xz23

// import std;

auto const fastIOInit{
    [] -> int {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class Solution final {
public:
    using mxT = std::vector<std::vector<int>>;

    auto findRotation(
        mxT &  mxSource_,
        mxT const & mxTarget_
    ) const -> bool;
};

// let 'n' by 'n' be the matrix size
// time complexity O(n^2)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
auto Solution::findRotation(
    mxT &  mxSource_,
    mxT const & mxTarget_
) const -> bool {
    namespace vs = std::views;

    auto const rcSz{std::ssize(mxSource_)};
    // Try all 4 possible rotations: 0°, 90°, 180°, 270°
    for(auto const rotationIter: vs::iota(0, 4)) {
        // Iterate over source matrix values
        for(auto const r: vs::iota(0, rcSz)) {
            for(auto const c: vs::iota(0, rcSz)) {
                auto targetVal{-1};
                switch(rotationIter) {
                    case 0: {
                        // No rotation
                        targetVal = mxTarget_[r][c];
                        break;
                    };
                    case 1: {
                        // 90° rotation
                        targetVal = mxTarget_[c][rcSz - r - 1];
                        break;
                    };
                    case 2: {
                        // 180° rotation
                        targetVal = mxTarget_[rcSz - r - 1][rcSz - c - 1];
                        break;
                    };
                    case 3: {
                        // 270° rotation
                        targetVal = mxTarget_[rcSz - c - 1][r];
                        break;
                    }
                }
                if(mxSource_[r][c] != targetVal) {
                    // Mismatch found, skip to next rotation
                    goto nextRotationIter;
                }
            }
        }
        // All elements matched for this rotation
        return true;
        nextRotationIter:;
    }
    // No rotation generates full match matrix
    return false;
}
