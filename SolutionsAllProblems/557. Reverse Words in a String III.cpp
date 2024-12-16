// problem : https://leetcode.com/problems/reverse-words-in-a-string-iii/description/
// submission : https://leetcode.com/problems/reverse-words-in-a-string-iii/submissions/1480559590
// solution post : https://leetcode.com/problems/reverse-words-in-a-string-iii/solutions/6154055/c-modern-readable-code-beats-100-runtime-o2sv


// #include <string>


class Solution {
public:
    // let 'n' be a parameter 'str' length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    std::string reverseWords(std::string str) const {
        for(auto first{str.begin()}, last{str.begin()}, end{str.end()};
            last < end;
        ) {
            while(++last < end && *last != ' ') {}
            reverse(first, last++);
            first = last;
        }
        return str;
    }
private:
    void reverse(
        auto first,
        auto last
    ) const {
        auto temp{'?'};
        while(first < --last) {
            temp = *first;
            *first++ = *last;
            *last = temp;
        }
    }
};
