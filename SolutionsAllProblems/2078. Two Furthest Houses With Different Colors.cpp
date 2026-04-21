// problem : https://leetcode.com/problems/two-furthest-houses-with-different-colors/description
// submission : https://leetcode.com/problems/two-furthest-houses-with-different-colors/submissions/1984645787
// solution post : https://leetcode.com/problems/two-furthest-houses-with-different-colors/solutions/8036844/
//    c-modern-readable-code-beats-100-runtime-8lu9

// Approach : Greedy Two-Pointers (Inward Search)
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the number of houses
// complexity :  O(n)
// complexity : O(1)

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

class Solution final {
public:
    // Finds the maximum distance between two houses with different colors.
    auto maxDistance(std::vector<int>& colors_) const -> int;
};

// Implements maxDistance using a greedy approach inward from the endpoints.
auto Solution::maxDistance(std::vector<int>& colors_) const -> int {
    namespace vs = std::views;

    auto const colorsSz{std::ssize(colors_)};
    // Iterate j as the reduction amount from the maximum possible distance.
    for(auto const j: vs::iota(0z, colorsSz)) {
        // Check if start differs from end-j, or if start+j differs from end.
        if(colors_.front() != colors_[colorsSz - j - 1] || colors_[j] != colors_.back()) {
            // Calculate the maximum distance found at the current step j.
            auto const maxDist{colorsSz - j - 1};
            return maxDist;
        }
    }

    // Return -1 as a fallback if no two houses have different colors.
    return -1;
}
