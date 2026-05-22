// problem : https://leetcode.com/problems/search-in-rotated-sorted-array/description
// submission : https://leetcode.com/problems/search-in-rotated-sorted-array/submissions/2010088699
// solution post : https://leetcode.com/problems/search-in-rotated-sorted-array/solutions/8286826/
//        c-modern-readable-code-beats-100-runtime-dxxi

// Approach : One-Pass Binary Search
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the count of numbers
// complexity :  O(log(n))
// complexity : O(1)

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto search(
        std::vector<int> const & nums_,
        int const target_
    ) -> int;

private:
    // Sentinel return value for absent target
    static auto constexpr kNotFound{-1};
};

auto Solution::search(
    std::vector<int> const & nums_,
    int const target_
) -> int {
    auto const begin{nums_.cbegin()};
    auto const end{nums_.cend()};

    // Modified binary search over the rotated space
    for(
        auto    left{begin},
                right{end - 1},
                mid{begin + (end - begin - 1) / 2};
        left <= right;
        mid = left + (right - left) / 2
    ) {
        // Target match located
        if(*mid == target_) {
            return mid - begin;
        // Left segment is continuously sorted
        } else if(*mid >= *left) {
            // Target is bounded within the sorted left segment
            if(
                *left <= target_ &&
                target_ < *mid
            ) {
                right = mid - 1;
            // Target must reside in the rotated right segment
            } else {
                left = mid + 1;
            }
        // Right segment is continuously sorted
        } else {
            // Target is bounded within the sorted right segment
            if(
                *mid < target_ &&
                target_ <= *right
            ) {
                left = mid + 1;
            // Target must reside in the rotated left segment
            } else {
                right = mid - 1;
            } 
        }
    }

    return kNotFound;
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
