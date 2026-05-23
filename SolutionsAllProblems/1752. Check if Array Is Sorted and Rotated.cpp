// problem : https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/description     
// submission : https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/submissions/2011062116
// solution post : https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/solutions/8288965/
//        c-modern-readable-code-beats-100-runtime-sal1

// Approach : Single Pass Pivot Counting
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the number of elements in the array
// complexity :  O(n)
// complexity : O(1)

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto check(std::vector<int> const & nums_) -> bool;
};

auto Solution::check(std::vector<int> const & nums_) -> bool {
    // Count rotation pivot points
    auto pivotCnt{0};

    for(auto num{std::next(nums_.cbegin())}; num < nums_.cend(); ++num) {
        // Multiple pivot points invalidate the single rotation constraint
        if(*std::prev(num) > *num && ++pivotCnt > 1) {
            return false;
        } 
    }

    // Ensure the rotated tail connects validly to the original head
    if(pivotCnt == 1) {
        return nums_.front() >= nums_.back();
    }

    return true;
}

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
