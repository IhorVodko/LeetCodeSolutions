// problem : https://leetcode.com/problems/add-binary/description/ 
// submission : https://leetcode.com/problems/add-binary/submissions/1475482891
// solution post : https://leetcode.com/problems/add-binary/solutions/6133622/c-modern-readable-code-beats-100-runtime


// #include <string>
// #include <utility>


class Solution {
public:
    // let 'n' be an input str1 length
    // 'm' - an input str2 lenght
    // time complexity O(max(n, m))
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    std::string addBinary(
        std::string str1,
        std::string str2
    ) const {
        auto const length1{str1.length()};         
        auto const length2{str2.length()};
        length1 < length2 ? std::swap(str1, str2) : void();
        std::string result;
        auto carry{size_t{0}};
        for(auto chr1{str1.crbegin()}, chr2{str2.crbegin()}, end1{str1.crend()},
            end2{str2.crend()}; chr1 < end1; ++chr1
        ) {
            *chr1 == '1' ? ++carry : size_t{};
            (chr2 < end2 && *chr2++ == '1') ? ++carry : int{};
            result.push_back(carry % 2 == 1 ? '1' : '0');
            carry /= 2;
        }
        carry == 1 ? result.push_back('1') : void();
        return {result.rbegin(), result.rend()};
    }
};
