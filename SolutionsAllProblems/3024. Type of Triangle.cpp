// problem : https://leetcode.com/problems/type-of-triangle/description/
// submission : https://leetcode.com/problems/type-of-triangle/submissions/1638645461
// solution post : https://leetcode.com/problems/type-of-triangle/solutions/6760880/
//    c-modern-readable-code-beats-100-by-cybe-x879

// #include <vector>

namespace Utility {
    auto constexpr kEquilateral{"equilateral"};
    auto constexpr kIsosceles{"isosceles"};
    auto constexpr kScalene{"scalene"};
    auto constexpr kNone{"none"};
}

class Solution {
public:
/*
time complexity O(1)
space complexity O(1)
runtime 0 ms, beats 100.00 %
*/
    std::string triangleType(std::vector<int> const & lengthes_) const;
};

std::string Solution::triangleType(std::vector<int> const & lengthes_) const {
    using namespace Utility; 
    auto const l1{lengthes_.at(0)};
    auto const l2{lengthes_.at(1)};
    auto const l3{lengthes_.at(2)};
    if(l1 == l2 && l2 == l3) {
        return kEquilateral;     
    } else if(l1 < l2 + l3 && l2 < l1 + l3 && l3 < l1 + l2) {
        if(l1 == l2 || l1 == l3 || l2 == l3) {
            return kIsosceles;
        } else {
            return kScalene;
        }
    }
    return kNone;
}
