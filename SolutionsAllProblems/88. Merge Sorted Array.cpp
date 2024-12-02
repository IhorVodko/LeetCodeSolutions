// problem : https://leetcode.com/problems/merge-sorted-array/submissions/1464229321/
// submission : https://leetcode.com/problems/merge-sorted-array/submissions/1464229321
// solution post: https://leetcode.com/problems/merge-sorted-array/solutions/6088893/c-modern-readable-code-beats-100-runtime

// #include <vector>

class Solution{
public:
    // let 'n' and 'm' be input sizes
    // time complexity O(n + m)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
   void merge(
        std::vector<int> & nums1,
        int const notZeros1,
        std::vector<int> & nums2,
        int const notZeros2
    ){
        if(nums1.empty() || nums2.empty()) {
            return;
        }
        if(notZeros1 == 0){
            std::swap(nums1, nums2);
            return;
        }
        auto last{int(nums1.size() - 1)};
        auto num1{int(notZeros1 - 1)};
        auto num2{int(notZeros2 - 1)};
        while(last >= 0 && num1 >= 0 && num2 >= 0) {
            nums1.at(last--) = nums1.at(num1) >= nums2.at(num2) ?
                nums1.at(num1--) : nums2.at(num2--);
        }
        while(num2 >= 0 && last >=0) {
            nums1.at(last--) = nums2.at(num2--);
        }
    }
};
