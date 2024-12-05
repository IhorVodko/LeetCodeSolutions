// problem : https://leetcode.com/problems/move-pieces-to-obtain-a-string/description/
// submission : https://leetcode.com/problems/move-pieces-to-obtain-a-string/submissions/1471017520
// solution post : https://leetcode.com/problems/move-pieces-to-obtain-a-string/solutions/6116292/c-modern-readable-code


// #include <string>


class Solution {
public:
    // let 'n' be an input length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 4 ms, beats 90.23 %
    bool canChange(
        std::string const start,
        std::string const target
    ) const {
        constexpr auto l{'L'};
        constexpr auto r{'R'};
        constexpr auto _{'_'};
        auto const length{start.size()};
        for(auto indxS{size_t{0}}, indxT{size_t{0}};; ++indxS, ++indxT) {
            while(indxS < length && start.at(indxS) == _) {
                ++indxS;
            }
            while(indxT < length && target.at(indxT) == _) {
                ++indxT;
            }
            if(indxS == length && indxT == length) {
                return true;
            }
            if(indxS == length || indxT == length) {
                return false;
            }
            if(start.at(indxS) != target.at(indxT) || 
                (start.at(indxS) == l && indxS < indxT) ||
                (target.at(indxT) == r && indxS > indxT)
            ) {
                return false;
            }
        }
        return true;
    }
};
