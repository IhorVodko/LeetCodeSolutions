// problem : https://leetcode.com/problems/check-if-all-1s-are-at-least-length-k-places-away/description/
// submission : https://leetcode.com/problems/check-if-all-1s-are-at-least-length-k-places-away/submissions/1832562103
// solution post : https://leetcode.com/problems/check-if-all-1s-are-at-least-length-k-places-away/solutions/7355819/
//    c-modern-readable-code-beats-100-runtime-w75b

// import std;

class Solution {
public:
// let 'n' be the number of given numbers
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto kLengthApart(
        std::span<int const> const nums_,
        int const minDist_
    ) const -> bool;
};

auto Solution::kLengthApart(
    std::span<int const> const nums_,
    int const minDist_
) const -> bool {
    auto dist{minDist_};
    for(auto const num: nums_) {
        if(num == 0) {
            ++dist;
        } else if(num == 1) {
            if(dist < minDist_) {
                return false;
            }
            dist = 0;
        }
    } 
    return true; 
}
