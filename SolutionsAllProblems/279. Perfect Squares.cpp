// problem : https://leetcode.com/problems/perfect-squares/description/
// submission : https://leetcode.com/problems/perfect-squares/submissions/1546626792
// solution post : https://leetcode.com/problems/perfect-squares/solutions/6434842/
//     c-modern-readable-code-beats-100-runtime-84pm

// let 'n' be a given number
// time complexity O(n^(1/2))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int numSquares(int n) const {
        while(n % 4 == 0) {
            n /= 4;
        } 
        if(n % 8 == 7) {
            return 4;
        }
        if(IsPerfectSquare(n)) {
            return 1;
        }
        for(auto num{1}; num * num <= n; ++num) {
            if(IsPerfectSquare(n - num * num)) {
                return 2;
            }
        }
        return 3;
    }
private:
    bool IsPerfectSquare(
        int const num
    ) const {
        auto const sqrRoot{static_cast<int>(std::sqrt(num))};
        return sqrRoot * sqrRoot == num;
    }
};
