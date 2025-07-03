// problem : https://leetcode.com/problems/find-the-k-th-character-in-string-game-i/description/
// submission : https://leetcode.com/problems/find-the-k-th-character-in-string-game-i/submissions/1685421928
// solution post : https://leetcode.com/problems/find-the-k-th-character-in-string-game-i/solutions/6916780/
//    c-modern-readable-code-beats-100-runtime-wa8q

// #include <cmath>

class Solution {
public:
// let 'n' be a given index of the target character
// time complexity O(log2(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    char kthCharacter(int const idxOfTargetChr_) const;
};

char Solution::kthCharacter(int const idxOfTargetChr_) const {
    auto chrTarget{0};
    int temp{0};
    auto idxOfTargetChr(idxOfTargetChr_);
    while(idxOfTargetChr != 1) {
        temp = static_cast<int>(std::log2(idxOfTargetChr));
        if(static_cast<int>(std::pow(2, temp)) == idxOfTargetChr) {
            --temp;
        }
        idxOfTargetChr -= static_cast<int>(std::pow(2, temp));
        ++chrTarget;
    }
    return 'a' + chrTarget;
}
