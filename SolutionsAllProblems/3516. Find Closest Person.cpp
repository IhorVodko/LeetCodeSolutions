// problem : https://leetcode.com/problems/find-closest-person/description
// submission : https://leetcode.com/problems/find-closest-person/submissions/1759467009
// solution post : https://leetcode.com/problems/find-closest-person/solutions/7155455/
//    c-modern-readable-code-beats-100-runtime-w475/

// #include <cmath>

class Solution {
public:
// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    int findClosest(
        int const pos1_,
        int const pos2_,
        int const pos3_
    ) const;
};

int Solution::findClosest(
    int const pos1_,
    int const pos2_,
    int const pos3_
) const {
    auto const distance1{std::abs(pos3_ - pos1_)};
    auto const distance2{std::abs(pos3_ - pos2_)};
    auto const res{
        distance1 == distance2 ?
            0 :
            distance1 < distance2 ? 1 : 2
    };
    return res;
}
