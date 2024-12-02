// problem : https://leetcode.com/problems/valid-mountain-array/description/
// submission : https://leetcode.com/problems/valid-mountain-array/submissions/1465237757
// solution post: https://leetcode.com/problems/valid-mountain-array/solutions/6092728/c-modern-readable-code

// #include <vector>


class Solution{
public:
    // let 'n' be an input size
    // time complexity O(n)
    // space complexity O(1)
    // runtime 14 ms, beats 90.96 %
    bool validMountainArray(std::vector<int> const & arr) const {
        constexpr auto requiredMinSize{3};
        if(arr.size() < requiredMinSize) {
            return false;
        }
        auto first{arr.cbegin()};
        auto second{first + 1};
        auto end{arr.cend()};
        while(*first++ < *second++) {
            if(second == end){
                return false;
            }
        }
        --first;
        --second;
        if(first == arr.cbegin()){
            return false;
        }
        while(*first++ > *second++) {
            if(second == end){
                return true;
            }
        }
        return false;
    }
};
