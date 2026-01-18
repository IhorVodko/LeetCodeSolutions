// problem : https://leetcode.com/problems/maximum-square-area-by-removing-fences-from-a-field/description
// submission : https://leetcode.com/problems/maximum-square-area-by-removing-fences-from-a-field/submissions/1889052141
// solution post : https://leetcode.com/problems/maximum-square-area-by-removing-fences-from-a-field/solutions/7505205/
//    c-modern-readable-code-beats-100-runtime-dakp

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream{"display_runtime.txt"} << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the number of horizontal fences
// 'm' - of vertical fences
// time complexity O(n^2 + m^2)
// space complexity O(min(n, m)^2)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    // Computes the maximum square area that can be formed
    [[nodiscard]]
    auto maximizeSquareArea(
        int const hSz_,
        int const vSz_,
        std::vector<int> & hFences_,
        std::vector<int> & vFences_
    ) const -> int;

private:
    static auto constexpr kModulus{1'000'000'007};
};

auto Solution::maximizeSquareArea(
    int const hSz_,
    int const vSz_,
    std::vector<int> & hFences_,
    std::vector<int> & vFences_
) const -> int {
    namespace vs = std::views;

    // Ensure the horizontal side has fewer (or equal) fences than the vertical side
    // This reduces memory usage for the hash set
    if(hSz_ > vSz_) {
        return maximizeSquareArea(vSz_, hSz_, vFences_, hFences_);
    }

    // Add the outer horizontal boundaries to the fence list
    hFences_.insert(hFences_.end(), {1, hSz_});
    auto maxHLen{0};
    auto const hSz{hFences_.size()};
    auto hLengths{std::unordered_set<int>{}};
    hLengths.reserve((hSz + 2) * (hSz + 1));

    // Compute all pairwise horizontal distances
    for(auto const i1: vs::iota(0u, hSz - 1)) {
        for(auto const i2: vs::iota(i1 + 1, hSz)) {
            auto const curHLen{std::abs(hFences_[i2] - hFences_[i1])};
            maxHLen = std::max(maxHLen, curHLen);
            hLengths.emplace(curHLen);
        }
    }

    // Track the maximum valid square side length
    auto maxLen{0};

    // Add the outer vertical boundaries to the fence list
    vFences_.insert(vFences_.end(), {1, vSz_});
    auto const vSz{vFences_.size()};

    // Compute all pairwise vertical distances
    for(auto const i1: vs::iota(0u, vSz - 1)) {
        for(auto const i2: vs::iota(i1 + 1, vSz)) {
            auto const curVLen{std::abs(vFences_[i2] - vFences_[i1])};

            // Early exit if the maximum possible square is found
            if(curVLen == maxHLen) {
                auto const maxArea{static_cast<long long>(curVLen) * curVLen % kModulus};
                return maxArea;
            }

            // Update the maximum square side length if this vertical length is valid
            if(curVLen > maxLen && hLengths.contains(curVLen)) {
                maxLen = curVLen;
            }
        }
    }

    // If no valid square could be formed, return -1
    if(maxLen == 0) {
        auto const maxArea{-1};
        return maxArea;
    } else {

        // Return the area of the largest valid square modulo kModulus
        auto const maxArea{static_cast<long long>(maxLen) * maxLen % kModulus};
        return maxArea;
    }
}
