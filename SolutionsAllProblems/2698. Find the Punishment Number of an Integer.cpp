// problem :  https://leetcode.com/problems/find-the-punishment-number-of-an-integer/description/
// submission : https://leetcode.com/problems/find-the-punishment-number-of-an-integer/submissions/1544310375
// solution post : https://leetcode.com/problems/find-the-punishment-number-of-an-integer/solutions/6427057/
//     c-modern-readable-code-beats-100-runtime-ur1g

// let 'n' be a given integer
// time complexity O(n * 2^log10(n))
// space complexity O(log10(n))
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int punishmentNumber(int const n) const {
        auto punishmentNum{0};
        for(auto numCurr{0}; numCurr <= n; ++numCurr) {
            auto const numSquare{numCurr * numCurr};
            punishmentNum += DoesValidPartitionExist(numSquare, numCurr) ?
                numSquare : 0;
        }
        return punishmentNum;
    }
private:
    int DoesValidPartitionExist(
        int const num,
        int const target
    ) const {
        if(target < 0 || num < target) {
            return false;
        }
        if(num == target) {
            return true;
        }
        return DoesValidPartitionExist(num / 10, target - num % 10) ||
            DoesValidPartitionExist(num / 100, target - num % 100) ||
            DoesValidPartitionExist(num / 1000, target - num % 1000);
    }
};
