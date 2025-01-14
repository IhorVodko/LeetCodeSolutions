// problem : https://leetcode.com/problems/perform-string-shifts/description/
// submission : https://leetcode.com/problems/perform-string-shifts/submissions/1508810116
// solution post : https://leetcode.com/problems/perform-string-shifts/solutions/6281365/c-modern-readable-code-beats-100-runtime-s7zf

// #include <algorithm>
// #include <string>
// #include <vector>

// let 's' be a parameter 'str' length
// 'sh' - parameter 'shifts' length
// time complexity O(max(s, sh))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using MtxT = std::vector<std::vector<int>>;
    std::string stringShift(
        std::string & str,
        MtxT const & shifts
    ) const {
        auto shift{std::accumulate(shifts.begin(), shifts.end(), 0,
            [] (auto const init, auto const & shift) {
                return init + (shift.at(0) == 1 ? -1 : 1) * shift.at(1);
        })};
        auto sz{static_cast<int>(str.length())};
        shift = ((shift % sz) + sz) % sz;
        std::rotate(str.begin(), str.begin() + shift, str.end());
        return str;
    }
};
