// problem : https://leetcode.com/problems/count-and-say/description/
// submission : https://leetcode.com/problems/count-and-say/submissions/1611840349
// solution post : https://leetcode.com/problems/count-and-say/solutions/6668095/
//    c-modern-readable-code-optimal-time-comp-scqo

// #include <string>

// let 'n' be a given value
// time complexity O(4^(n / 3))
// space complexity O(4^(n / 3))
// runtime 3 ms, beats 81.96 %
class Solution {
public:
    std::string countAndSay(int const n_) const {
        auto rleStr{"1"};
        return DoRle(rleStr, n_ - 1);
    }
private:
    std::string DoRle(
        std::string const & rleStr_,
        int const n_
    ) const {
        if(n_ == 0) {
            return rleStr_;
        }
        auto rleStrNew{std::string{}};
        auto rleStr_End{rleStr_.end()};
        for(auto chr{rleStr_.begin()}; chr < rleStr_End;) {
            auto const chrCurr{*chr};
            auto chrCurrCount{0};
            while(chr < rleStr_End && chrCurr == *chr) {
                ++chrCurrCount;
                ++chr;
            }
            rleStrNew += std::to_string(chrCurrCount) + chrCurr;
        }
        return DoRle(rleStrNew, n_ - 1); 
    }
};

