// problem : https://leetcode.com/problems/check-if-n-and-its-double-exist/description/
// submission : https://leetcode.com/problems/check-if-n-and-its-double-exist/submissions/1465209501
// solution post: https://leetcode.com/problems/check-if-n-and-its-double-exist/solutions/6092604/c-modern-readable-code-beats-100-runtime

// #include <vector>
// #include <unordered_map>


class Solution{
public:
    // let 'n' be an input size
    // time complexity O(n)
    // space complexity O(n)
    // runtime 0 ms, beats 100.00 %
    // memory 14.32 mb, beats 12.36 %
    bool checkIfExist(std::vector<int> const & arr) const {
        // for educational purposes no stl algos are used
        enum class Times {X1, X2};
        auto doubleNums{std::unordered_map<int, Times>{}};
        for(auto const num: arr) {
            if((doubleNums.contains(num) && doubleNums.at(num) == Times::X2) ||
                (doubleNums.contains(num * 2) &&
                    doubleNums.at(num * 2) == Times::X1)
            ) {
                return true;
            }
            doubleNums[num] = Times::X1; 
            doubleNums[num * 2] = Times::X2; 
        }
        return false;
    }
};
