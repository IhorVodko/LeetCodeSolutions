// problem : https://leetcode.com/problems/largest-perimeter-triangle/description 
// submission : https://leetcode.com/problems/largest-perimeter-triangle/submissions/1786134070
// solution post : https://leetcode.com/problems/largest-perimeter-triangle/solutions/7233298/
//    c-modern-readable-code-beats-100-runtime-6qv6

// import std;

class Solution {
public:
// let 'n' be a count of the given numbers
// time complexity O(n * log(n))
// space complexity O(log(n))
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto largestPerimeter(std::vector<int> & nums_) const -> int;
};

auto Solution::largestPerimeter(std::vector<int> & nums_) const -> int {
    namespace ranges = std::ranges;
    namespace views = std::views;

    ranges::sort(nums_, std::greater{});
    for(auto idx: views::iota(0u, nums_.size() - 2)) {
        auto const side1{nums_.at(idx)};
        auto const side2{nums_.at(idx + 1)};
        auto const side3{nums_.at(idx + 2)};
        if(side1 < side2 + side3) {
           auto const maxPerimeter{side1 + side2 + side3};
           return maxPerimeter;
        }
    }
    return 0;
}
