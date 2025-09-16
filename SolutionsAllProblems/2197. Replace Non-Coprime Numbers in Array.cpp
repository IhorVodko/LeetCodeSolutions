// problem : https://leetcode.com/problems/replace-non-coprime-numbers-in-array/description/
// submission : https://leetcode.com/problems/replace-non-coprime-numbers-in-array/submissions/1772890315
// solution post : https://leetcode.com/problems/replace-non-coprime-numbers-in-array/solutions/7196735/
//    c-modern-readable-code-optimal-time-comp-511p

// import std;

class Solution {
public:
// let 'n' be a length of the given
// 'm' be a maximum allowed input number
// time complexity O(n * log(m))
// space complexity O(1)
// runtime 9 ms, beats 94.91 %
    [[nodiscard]]
    auto replaceNonCoprimes(
        std::vector<int> & nums_
    ) const -> std::vector<int>;
private:
    static inline bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
};

auto Solution::replaceNonCoprimes(
    std::vector<int> & nums_
) const -> std::vector<int> {
    auto resNums{std::vector<int>{}};
    auto const numsSz{std::ssize(nums_)};
    resNums.reserve(numsSz);
    for(auto currNum: nums_) {
        while(!resNums.empty()) {
            auto const prevNum{resNums.back()};
            auto gcd{std::gcd(prevNum, currNum)};
            if(gcd > 1) {
                resNums.pop_back();
                currNum = prevNum / gcd * currNum;
            } else {
                break;
            }
        }
        resNums.emplace_back(currNum);
    }
    return resNums;
}
