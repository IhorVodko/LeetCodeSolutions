// problem : https://leetcode.com/problems/find-minimum-in-rotated-sorted-array
// submission : https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/submissions/2003944412
// solution post : https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/solutions/6720918/
//        c-modern-readable-code-beats-100-runtime-4hrz

// Approach : Declarative Binary Search
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the count of numbers
// complexity :  O(log(n))
// complexity : O(1)

// import std;

namespace {

// Initializer to configure fast I/O before main() runs
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
    [[nodiscard]]
    auto findMin(std::vector<int> const & nums_) const -> int;
};

auto Solution::findMin(std::vector<int> const & nums_) const -> int {
        // Binary searches the boundary between the left and right sorted portions of the
        // rotated array
        return *std::ranges::partition_point(
            nums_,
            std::bind_front(std::less{}, nums_.back())
        );
}
