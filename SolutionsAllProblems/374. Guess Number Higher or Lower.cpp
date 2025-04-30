// problem : https://leetcode.com/problems/guess-number-higher-or-lower/description/
// submission : https://leetcode.com/problems/guess-number-higher-or-lower/submissions/1621988276
// solution post : https://leetcode.com/problems/guess-number-higher-or-lower/solutions/6702257/
//     c-modern-readable-code-beats-100-runtime-cyw6

// #include <cmath>
// #include <limits>

/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

// let 'n' be the given number
// time complexity O(log(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int guessNumber(int const n) const {
        auto result{std::numeric_limits<int>::min()};
        auto left{1};
        auto right{n};
        auto mid{left + (right - left) / 2}; 
        auto curcuitBreaker{static_cast<int>(std::ceil(std::log2(n)))};
        do {
            result = ::guess(mid);
            if(result == -1) {
                right = mid - 1;
            } else if(result == 1) {
                left = mid + 1;
            } else {
                return mid;
            }
            mid = left + (right - left) / 2;
        } while(--curcuitBreaker >= 0);
        return -1;
    }
};
