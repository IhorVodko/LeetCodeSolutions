// problem : https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/description/ 
// submission : https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/submissions/1468693036
// solution post : https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/solutions/6106201/c-modern-readable-code-beats-100-runtime

// #include <algorithm>
// #include <vector>

class Solution{
public:
    // let 'n' be an input size
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    std::vector<int> findDisappearedNumbers(std::vector<int> & nums) {
        auto temp{int(0)};
        for(auto & num : nums) {
            temp = std::abs(num) - 1;
            nums.at(temp) *= nums.at(temp) > 0 ? -1 : 1;
        }
        auto writer{size_t(0)};
        auto reader{size_t{0}};
        while(reader < nums.size()){
            if(nums.at(reader++) > 0) {
                nums.at(writer++) = reader;
            }
        }
        return {nums.begin(), nums.begin() + writer};
    }
};
