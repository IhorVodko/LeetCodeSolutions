// problem : https://leetcode.com/problems/shifting-letters-ii/description/
// submission : https://leetcode.com/problems/shifting-letters-ii/submissions/1499815212
// solution post : https://leetcode.com/problems/shifting-letters-ii/solutions/6240805/c-modern-readable-code-beats-100-runtime-tllf

// #include <algorithm>
// #include <string>
// #include <vector>

// let 's' be a parameter 'str' length
// 'sh' - a parameter 'shifts' length
// time complexity O(s + sh)
// space complexity O(s)
// runtime 0 ms, beats 100.00 %
namespace Utility {
    auto constexpr alphabetSize{26};
    auto constexpr alphabetStart{'a'};
}

class Solution {
public:
    string shiftingLetters(
        std::string & str,
        std::vector<std::vector<int>> const & shifts
    ) const {
        using namespace Utility;
        auto finalShiftsCount{std::vector<int>(str.size(), 0)};
        for(auto const & shift: shifts) {
            finalShiftsCount.at(shift.at(0)) += shift.at(2) == 0 ? -1 : 1; 
            if(shift.at(1) + 1 < finalShiftsCount.size()) {
                finalShiftsCount.at(shift.at(1) + 1) +=
                    shift.at(2) == 0 ? 1 : -1;
            }
        }
        auto shiftsCount{0};
        std::transform(str.cbegin(), str.cend(), finalShiftsCount.cbegin(),
            str.begin(), [&] (auto const chr, auto const shift) {
                shiftsCount += shift % alphabetSize;
                if(shiftsCount < 0) {
                    shiftsCount += alphabetSize;
                } 
                return alphabetStart + (chr - alphabetStart + shiftsCount) %
                    alphabetSize;
        });
        return str;
    }
};
