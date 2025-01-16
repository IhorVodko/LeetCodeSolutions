// problem : https://leetcode.com/problems/bitwise-xor-of-all-pairings/description/
// submission : https://leetcode.com/problems/bitwise-xor-of-all-pairings/submissions/1510781212
// solution post : https://leetcode.com/problems/bitwise-xor-of-all-pairings/solutions/6290921/c-modern-readable-code-beats-100-runtime-f9hp

// #include <algorithm>
// #include <vector>

// let 'n1' be a parameter 'nums1' length
// 'n2' - parameter 'nums2' length
// time complexity O(n1 + n2)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int xorAllNums(
        std::vector<int> const & nums1,
        std::vector<int> const & nums2
    ) const {
        return (isOdd(nums2.size()) ? DoXorAll(nums1) : 0) ^
            (isOdd(nums1.size()) ? DoXorAll(nums2) : 0);
    }
private:
    bool isOdd(int const num) const {
        return num % 2 ? 1 : 0;
    }
    int DoXorAll(std::vector<int> const & nums) const {
        return std::accumulate(nums.begin(), nums.end(), 0, [] (
                auto const init,
                auto const num
            ) {
                return init ^ num;

        });
    }
};
