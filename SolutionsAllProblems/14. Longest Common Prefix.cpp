// problem :  https://leetcode.com/problems/longest-common-prefix/description/
// submission : https://leetcode.com/problems/longest-common-prefix/submissions/1457529731
// solution post: https://leetcode.com/problems/longest-common-prefix/solutions/6063354/c-modern-readable-code-beats-100-of-runtime

// #include <algorithm>
// #include <string>
// #include <vector>

class Solution {
public:
    // let 'S' be a sum of all letters from words in the input array
    // time complexity O(S)
    // space complexity O(1)
    // runtime 0 ms, beats 100 %
    std::string longestCommonPrefix(std::vector<std::string> & strs){
        if(strs.empty()){
            return "";
        }
        auto strMin{std::min_element(std::cbegin(strs), std::cend(strs), [&](
            auto const & str1, auto const & str2){
                return str1.length() < str2.length();})};
        size_t indx{0};
        for(; indx < strMin->size(); ++indx){
            if(std::any_of(std::cbegin(strs), std::cend(strs),[=]
                (auto const & str) {return str.at(indx) != strMin->at(indx);})
            ){
                break;
            }
        }
        return strMin->substr(0, indx); 
    }
};
