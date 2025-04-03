// problem : https://leetcode.com/problems/shortest-way-to-form-string/description/
// submission : https://leetcode.com/problems/shortest-way-to-form-string/submissions/1595963774
// solution post : https://leetcode.com/problems/shortest-way-to-form-string/solutions/6612606/
//     c-modern-readable-code-beats-100-runtime-7qfm

// #include <string>
// #include <vector>

namespace Utility {
    auto constexpr alphabetSize{26};
    auto constexpr alphabetStart{'a'};
}

// let 's' be a length of the source string
// 't' - of the target string
// time complexity O(s + t)
// space complexity O(s)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int shortestWay(
        std::string const & source_,
        std::string const & target_
    ) const {
        using namespace Utility;
        auto const sourceSz{source_.size()};
        auto nextOcurrence{std::vector<std::vector<int>>(sourceSz,
            std::vector<int>(alphabetSize, 0))};
        for(auto c{0}; c < alphabetSize; ++c) {
            nextOcurrence.back()[c] = -1;
        }
        nextOcurrence.back().at(ToNum(source_.back())) = sourceSz - 1;
        for(auto i{static_cast<int>(sourceSz) - 2}; i >= 0; --i) {
            for(auto c{0}; c < alphabetSize; ++c) {
                nextOcurrence[i][c] = nextOcurrence[i + 1][c];
            }
            nextOcurrence[i][ToNum(source_[i])] = i;
        } 
        auto sourceIterator{0};
        auto count{1};
        for(auto c: target_) {
            c -= alphabetStart;
            if(nextOcurrence.at(0).at(c) == -1) {
                return -1;
            }
            if(sourceIterator == sourceSz ||
                nextOcurrence.at(sourceIterator).at(c) == -1
            ) {
                ++count;
                sourceIterator = 0;
            }
            sourceIterator = nextOcurrence.at(sourceIterator).at(c) + 1;
        }
        return count;
    }
private:
    size_t ToNum(char const chr) const {
        using namespace Utility;
        return chr - alphabetStart;
    }
};
