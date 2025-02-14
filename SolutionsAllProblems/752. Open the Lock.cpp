// problem : https://leetcode.com/problems/open-the-lock/submissions/1543026642/
// submission : https://leetcode.com/problems/open-the-lock/submissions/1543026642
// solution post : https://leetcode.com/problems/open-the-lock/solutions/6422382/
//     c-modern-readable-code-beats-93-runtime-guald

// #include <queue>
// #include <string>

namespace Constants {
    auto constexpr combSz{4};
    auto constexpr delta{1};
    auto constexpr minDigit{'1'};
    auto constexpr maxDigit{'9'};
    auto constexpr initialComb{std::string{"0000"}};
}

// since amount of wheels is given as 4 and each wheel has 10 digits,
// so finding a target combination is garanteed among 10^4 tryies which is constant
// extra space required is also constant as 10^4 combinations
// time complexity O(1)
// space complexity O(1)
// runtime 86 ms, beats 92.55 %
class Solution {
public:
    int openLock(
        std::vector<std::string> const & deadends,
        std::string const & target
    ) const {
        using namespace Constants;
        if(initialComb == target) {
            return 0;
        }
        auto visitedCombs{std::unordered_set<std::string>{deadends.begin(),
            deadends.end()}}; 
        if(visitedCombs.contains(initialComb)) {
            return -1;
        }
        auto qCombs{std::queue<std::string>{}};
        qCombs.emplace(initialComb);
        auto minTurnsCount{0};
        while(!qCombs.empty()) {
            auto levelSize{qCombs.size()};
            while(levelSize-- > 0) {
                auto comb{qCombs.front()};
                qCombs.pop();
                for(auto digitIdx{0}; digitIdx < combSz; ++digitIdx) {
                    auto const oldDigit{comb.at(digitIdx)};
                    TurnUp(comb.at(digitIdx));
                    if(CheckComb(visitedCombs, qCombs, target, comb)) {
                        return ++minTurnsCount;
                    }
                    comb.at(digitIdx) = oldDigit;
                    TurnDown(comb.at(digitIdx));
                    if(CheckComb(visitedCombs, qCombs, target, comb)) {
                        return ++minTurnsCount;
                    }
                    comb.at(digitIdx) = oldDigit;  
                }
            }
            ++minTurnsCount;
        }
        return -1;
    }
private:
    void TurnUp(char & digit) const {
        using namespace Constants;
        digit = digit + delta > maxDigit ? minDigit : digit + delta;
    }
    void TurnDown(char & digit) const {
        using namespace Constants;
        digit = digit - delta < minDigit ? maxDigit : digit - delta;
    }
    bool CheckComb(
        std::unordered_set<std::string> & visitedCombs,
        std::queue<std::string> & qCombs,
        std::string const & target,
        std::string const & comb
    ) const {
        if(visitedCombs.contains(comb)) {
           return false; 
        }
        if(comb == target) {
            return true;
        }
        visitedCombs.emplace(comb);
        qCombs.emplace(comb);
        return false;
    }
};
