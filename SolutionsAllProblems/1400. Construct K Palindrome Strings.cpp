// problem : https://leetcode.com/problems/construct-k-palindrome-strings/description/
// submission : https://leetcode.com/problems/construct-k-palindrome-strings/submissions/1505397717
// solution post : https://leetcode.com/problems/construct-k-palindrome-strings/solutions/6266371/c-modern-readable-code-beats-100-runtime-da3s

// #include <bitset>
// #include <string>

namespace Utility {
    auto constexpr alphabetSize{26};
    auto constexpr alphabetStart{'a'};
}

// let 'n' be a parameter 'str' length
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    bool canConstruct(
        std::string const & str,
        int const numOfPalsRequired
    ) const {
        using namespace Utility;
        if(str.size() < numOfPalsRequired) {
            return false;
        }
        if(str.size() == numOfPalsRequired) {
            return true;
        }
        auto chrsCounts{std::bitset<alphabetSize>{}};
        for(auto const chr: str) {
            chrsCounts.flip(chr - 'a');
        }
        return chrsCounts.count() <= numOfPalsRequired ? true : false;
    }
};
