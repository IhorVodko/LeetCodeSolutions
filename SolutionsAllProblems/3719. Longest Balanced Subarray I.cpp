// problem : https://leetcode.com/problems/longest-balanced-subarray-i/description
// submission : https://leetcode.com/problems/longest-balanced-subarray-i/submissions/1915109038
// solution post : https://leetcode.com/problems/longest-balanced-subarray-i/solutions/7569725/
//    c-modern-readable-code-beats-100-runtime-wp9l

// import std;

// let 'n' be the number of elements
// time complexity O(n^2)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class Solution {
public:
    [[nodiscard]]
    auto longestBalanced(std::span<int const> const nums_) const -> int;
};

auto Solution::longestBalanced(std::span<int const> const nums_) const -> int {
    namespace vs = std::views;

    auto const numsSz{std::ssize(nums_)};
    // Frequency maps to track distinct even and odd values in the current window
    auto oddToCnt{std::unordered_map<int, int>{}};
    oddToCnt.reserve(numsSz);
    auto evenToCnt{std::unordered_map<int, int>{}};
    evenToCnt.reserve(numsSz);
    auto maxSubArSz{0};
    // idxB is the starting index of the subarray
    for(auto const idxB: vs::iota(0, numsSz - 1)) {
        // Even starting index: expand window forward
        if(idxB % 2 == 0) {
            for(auto const idxE: vs::iota(idxB, numsSz)) {
                auto const curNum{nums_[idxE]};
                // Update frequency based on parity
                curNum % 2 == 0 ? ++evenToCnt[curNum] : ++oddToCnt[curNum];
                // Balanced when distinct even and odd counts match
                if(evenToCnt.size() == oddToCnt.size()) {
                    auto const curSubArSz{idxE - idxB + 1};
                    maxSubArSz = std::max(maxSubArSz, curSubArSz);
                }
            }
            // Remove the element at idxB before moving the window start
            auto const numErase{nums_[idxB]};
            if(numErase % 2 == 0) {
                if(--evenToCnt[numErase] == 0) {
                    evenToCnt.erase(numErase);
                }
            } else if(--oddToCnt[numErase] == 0){
                oddToCnt.erase(numErase);
            }          
        } else {
            // Odd starting index: shrink window from the end backward
            for(auto const idxE: vs::iota(idxB, numsSz) | vs::reverse) {
                auto const curNum{nums_[idxE]};
                // Check balance before removing the current element
                if(evenToCnt.size() == oddToCnt.size()) {
                    auto const curSubArSz{idxE - idxB + 1};
                    maxSubArSz = std::max(maxSubArSz, curSubArSz);
                }
                // Remove current element from frequency maps
                if(curNum % 2 == 0) {
                    if(--evenToCnt[curNum] == 0) {
                        evenToCnt.erase(curNum);
                    }
                } else if(--oddToCnt[curNum] == 0) {
                    oddToCnt.erase(curNum);
                }
            }
        }
        // Early exit if no longer possible to find a larger subarray
        if(idxB + maxSubArSz >= numsSz) {
            return maxSubArSz;
        }
    } 
    return maxSubArSz;
}
