// problem : https://leetcode.com/problems/squares-of-a-sorted-array/description/
// submission : https://leetcode.com/problems/squares-of-a-sorted-array/submissions/1463435386
// solution post: https://leetcode.com/problems/squares-of-a-sorted-array/solutions/6085898/c-modern-readable-code-beats-100-runtime

// #include <cmath>
// #include <vector>


class Solution{
public:
    // let 'n' be an input length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100 %
    std::vector<int> sortedSquares(std::vector<int> const & nums) const {
        if(nums.size() == 1){
            return {nums.front() * nums.front()};
        }
        auto squaresSorted{std::vector<int>(nums.size(), 0)};
        auto itResult{std::rbegin(squaresSorted)};
        for(auto it1{std::cbegin(nums)}, it2{std::cend(nums) - 1}; it1 <= it2;
        ){
            *itResult++ = std::abs(*it1) >= std::abs(*it2) ? *it1 * *it1++ :
                *it2 * *it2--;
        }
        return squaresSorted;
    }
};
