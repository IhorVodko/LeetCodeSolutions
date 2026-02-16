// problem : https://leetcode.com/problems/add-binary/description/ 
// submission : https://leetcode.com/problems/add-binary/submissions/1475482891
// solution post : https://leetcode.com/problems/add-binary/solutions/6133622/c-modern-readable-code-beats-100-runtime


// import std;

// let 'n' be an input str1 length
// 'm' - an input str2 lenght
// time complexity O(max(n, m))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    std::string addBinary(
        std::string str1,
        std::string str2
    ) const {
        auto const length1{str1.length()};         
        auto const length2{str2.length()};
        // Ensure str1 is not shorter than str2 so that the main loop
        // only needs to check exhaustion for str2
        length1 < length2 ? std::swap(str1, str2) : void();
        std::string result;
        // Carry accumulates the sum of current bits plus previous carry
        auto carry{size_t{0}};
        // Iterate from least significant bit to most significant bit
        // using reverse iterators
        for(auto chr1{str1.crbegin()}, chr2{str2.crbegin()}, end1{str1.crend()},
            end2{str2.crend()}; chr1 < end1; ++chr1
        ) {
            // Add bit from str1 to carry if it is '1'
            *chr1 == '1' ? ++carry : size_t{};
            // Add bit from str2 to carry if available and equal to '1'
            // Advance chr2 only when it is valid
            (chr2 < end2 && *chr2++ == '1') ? ++carry : int{};
            // Current result bit is carry modulo 2
            result.push_back(carry % 2 == 1 ? '1' : '0');
            // Update carry for next iteration (integer division by 2)
            carry /= 2;
        }
        // If there is a remaining carry after processing all bits,
        // append it as the most significant bit
        carry == 1 ? result.push_back('1') : void();
        // The result was constructed in reverse order,
        // so return the reversed string
        return {result.rbegin(), result.rend()};
    }
};
