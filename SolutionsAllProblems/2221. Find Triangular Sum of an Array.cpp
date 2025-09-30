// problem : https://leetcode.com/problems/find-triangular-sum-of-an-array/description
// submission : https://leetcode.com/problems/find-triangular-sum-of-an-array/submissions/1787332535
// solution post : https://leetcode.com/problems/find-triangular-sum-of-an-array/solutions/7236734/
//    c-modern-readable-code-by-cyberartist-943y

// import std;

class Solution {
public:
// let 'n' be the length of the given array
// time complexity O(n ^ 2)
// space complexity O(1)
// runtime 198 ms, beats 26.56 %
    [[nodiscard]]
    auto triangularSum(std::vector<int> & nums_) const -> int;

private:
    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
};

auto Solution::triangularSum(std::vector<int> & nums_) const -> int {
    namespace views = std::views;

    auto numsSz{std::ssize(nums_)};
    while(--numsSz >= 0) {
        for(auto const idx: views::iota(0, numsSz)) {
            nums_.at(idx) = (nums_.at(idx) + nums_.at(idx + 1)) % 10; 
        }
    }
    auto const triangularSum{nums_.at(0)};
    return triangularSum;
}
