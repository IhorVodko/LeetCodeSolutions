// problem : https://leetcode.com/problems/third-maximum-number/description/
// submission : https://leetcode.com/problems/third-maximum-number/submissions/1461111679
// solution post: https://leetcode.com/problems/third-maximum-number/solutions/6076623/c-modern-readable-code-beets-100-runtime

// #include 
// #in

class Solution {
public:
    // let 'n' be an input length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100 %
    // memory 12.25 mb, beats 41.58 %
    int thirdMax(std::vector<int> const & nums) const {
        auto threeLargestNums{std::set<int>{{nums.front()}}};
        auto num{std::cbegin(nums)};
        auto end{std::cend(nums)};
        while(++num != end){
            threeLargestNums.insert(*num);
            if(threeLargestNums.size() >= 3){
                break;
            }
        }
        if(threeLargestNums.size() < 3){
            return *std::crbegin(threeLargestNums);
        }
        while(++num < end){
            if(*num <= *std::cbegin(threeLargestNums) ||
                threeLargestNums.count(*num) > 0
            ){
                continue;
            }        
            threeLargestNums.erase(std::begin(threeLargestNums));
            threeLargestNums.insert(*num);
        }
        return *std::cbegin(threeLargestNums); 
    }
};
