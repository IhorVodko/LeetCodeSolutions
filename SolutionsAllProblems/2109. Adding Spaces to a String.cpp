// problem : https://leetcode.com/problems/adding-spaces-to-a-string/description/
// submission : https://leetcode.com/problems/adding-spaces-to-a-string/submissions/1469410058
// solution post : https://leetcode.com/problems/adding-spaces-to-a-string/solutions/6109602/c-modern-readable-code-beats-100-runtime

// #include <string>
// #include <vector>


class Solution {
public:
    // let 'n' be an input length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 3 ms, beats 100.00 %
    std::string addSpaces(
        std::string str,
        std::vector<int> & spaces
    ) {
        auto charLast{int(str.size() - 1)};
        str.append(spaces.size(), ' ');
        auto last{int(str.size() - 1)};
        auto spaceIndx{0};
        while(!spaces.empty()) {
            spaceIndx = spaces.back();
            spaces.pop_back();
            while(charLast >= spaceIndx) {
                std::swap(str.at(charLast--), str.at(last--));
            }
            --last;
        }
        return str;   
    }
};
