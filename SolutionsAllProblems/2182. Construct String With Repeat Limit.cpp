// problem : https://leetcode.com/problems/construct-string-with-repeat-limit/description/
// submission : https://leetcode.com/problems/construct-string-with-repeat-limit/submissions/1481214425
// solution post : https://leetcode.com/problems/construct-string-with-repeat-limit/solutions/6156725/c-modern-readable-code-beats-100-runtime-308j


// #include <functional>
// #include <map>
// #include <string>


class Solution {
public:
    // let 'n' be a parameter 'str' length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 31 ms, beats 71.14 %
    std::string repeatLimitedString(
        std::string const str,
        int const repeatLimit
    ) const {
        auto charsCount{std::map<char, size_t, decltype(std::greater<char>())>{
            std::greater<char>()}};
        for(auto const chr: str) {
            ++charsCount[chr];
        }
        auto limit{0};
        auto result{std::string{}};
        while(!charsCount.empty()) {
            if(++limit <= repeatLimit) {
                result.push_back(charsCount.cbegin()->first);
                if(--charsCount.begin()->second == 0) {
                    charsCount.erase(charsCount.begin());
                    limit = 0;
                }
            } else {
                if(charsCount.size() < 2) {
                    return result;
                }
                limit = 0;
                result.push_back((++charsCount.cbegin())->first);
                if(--(++charsCount.begin())->second == 0) {
                    charsCount.erase(++charsCount.begin());
                }
            } 
        }
        return result;
    }
};
