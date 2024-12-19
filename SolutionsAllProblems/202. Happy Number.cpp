// problem : https://leetcode.com/problems/happy-number/description/
// submission : https://leetcode.com/problems/happy-number/submissions/1483178975
// solution post : https://leetcode.com/problems/happy-number/solutions/6165242/c-modern-readable-code-beats-100-runtime-zi4n


// #include <stack>
// #include <unordered_set>


class Solution {
public:
    // let 'n' be a number of digits of parameter 'n'
    // time complexity O(log(n))
    // space complexity O(log(n))
    // runtime 0 ms, beats 100.00 %
    bool isHappy(int n) {  
        while(sums.size() < maxSize) {
            itBool = sums.insert(Calculate(n));
            if(!itBool.second) {
                return false;
            }
            if(*itBool.first == happyNum) {
                return true;
            }
            n = *itBool.first;
        }
        return false;
    }
private:
    int Calculate(int n) {
        while( n > 0) {
            digits.push(n % radix);
            n /= radix;
        } 
        auto sum{0};
        while(!digits.empty()) {
            sum += digits.top() * digits.top();
            digits.pop();
        }
        return sum;
    }
    auto static constexpr happyNum{1};
    auto static constexpr maxSize{32 * 9 * 9};
    auto static constexpr radix{10};
    std::unordered_set<int> sums;
    std::stack<int> digits;
    std::pair<std::unordered_set<int>::const_iterator,bool> itBool;
};
