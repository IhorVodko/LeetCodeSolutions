// problem : https://leetcode.com/problems/push-dominoes/description
// submission : https://leetcode.com/problems/push-dominoes/submissions/1624475001
// solution post : https://leetcode.com/problems/push-dominoes/solutions/6711096/
//     c-modern-readable-code-optimal-time-comp-0h5s

// #include <algorithm>
// #include <string>
// #include <vector>

namespace Utility {
    auto constexpr kL{'L'};
    auto constexpr kR{'R'};
    auto constexpr kDot{'.'};
}

class Solution {
public:
// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(1)
// runtime 12 ms, beats 67.97 %
    std::string pushDominoes(std::string & dominoes_) const;
};

std::string Solution::pushDominoes(std::string & dominoes_) const {
    using namespace Utility;
    auto const dominoesCount{dominoes_.size()};
    auto forces{std::vector<int>{}};
    forces.reserve(dominoesCount);
    auto force{0};
    for(auto const domino: dominoes_) {
        if(domino == kR) {
            force = dominoesCount;
        } else if(domino == kL) {
            force = 0;
        } else {
            force = std::max(0, force - 1);
        }
        forces.emplace_back(force);
    }
    force = 0;
    for(auto i{static_cast<int>(dominoesCount - 1)}; i >= 0; --i) {
        if(dominoes_[i] == kL) {
            force = dominoesCount;
        } else if(dominoes_[i] == kR) {
            force = 0;
        } else {
            force = std::max(0, force - 1);
        }
        forces[i] -= force;
    }  
    auto result{std::string{}};
    for(auto i{0}; i < dominoesCount; ++i) {
        dominoes_[i] = forces[i] > 0 ? kR : forces[i] < 0 ? kL : kDot;
    }
    return dominoes_; 
}
