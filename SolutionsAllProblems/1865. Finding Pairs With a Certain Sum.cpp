// problem : https://leetcode.com/problems/finding-pairs-with-a-certain-sum/description
// submission : https://leetcode.com/problems/finding-pairs-with-a-certain-sum/submissions/1688859523
// solution post : https://leetcode.com/problems/finding-pairs-with-a-certain-sum/solutions/6929029/
//    c-modern-readable-code-optimal-time-comp-4tc9

// #include <vector>
// #include <unordered_map>

// let 'n1' be a length of the given first array of nums 
// let 'n2' - of the given second array of nums 
// runtime 71 ms, beats 82.68 %
class FindSumPairs {
public:
// time complexity O(n2)
// space complexity O(n2)
    FindSumPairs(
        std::vector<int> & nums1_,
        std::vector<int> & nums2_
    ):
        mNums1{nums1_},
        mNums2{nums2_}
    {
        for(auto const num2: mNums2) {
            ++num2ToCount[num2];
        }
    }
// time complexity O(1)
// space complexity O(1)
    void add(
        int const augendIdx_,
        int const adddend_
    ) {
        auto & num2{mNums2.at(augendIdx_)};
        if(--num2ToCount.at(num2) == 0) {
            num2ToCount.erase(num2);
        }
        num2 += adddend_;
        ++num2ToCount[num2];
    }
// time complexity O(n1)
// space complexity O(1)
    [[nodiscard]]
    int count(int const sumTarget_) {
        auto sumTargetCount{0};
        for(auto num1: mNums1) {
            auto const complement{sumTarget_ - num1};
            if(auto num2CountIt{num2ToCount.find(complement)};
                num2CountIt != num2ToCount.end()
            ) {
                sumTargetCount += num2CountIt->second;
            }
        }
        return sumTargetCount;
    }
private:
    std::vector<int> & mNums1;
    std::vector<int> & mNums2;
    std::unordered_map<int, size_t> num2ToCount;
    
};

/**
 * Your FindSumPairs object will be instantiated and called as such:
 * FindSumPairs* obj = new FindSumPairs(nums1, nums2);
 * obj->add(index,val);
 * int param_2 = obj->count(tot);
 */
