// problem : https://leetcode.com/problems/container-with-most-water/description/
// submission : https://leetcode.com/problems/container-with-most-water/submissions/1790857147
// solution post : https://leetcode.com/problems/container-with-most-water/solutions/7247402/
//    c-modern-readable-code-beats-100-runtime-k8ft

// import std;

class Solution {
public:
// let 'n' be the number of the given heights
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maxArea(std::vector<int> & heights_) const -> int;

private:
    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
};

auto Solution::maxArea(std::vector<int> & heights_) const -> int {
    auto maxVolume{0};
    auto side1{static_cast<int>(heights_.size()) - 1};
    for(auto heightLeft{heights_.cbegin()}, heightRight{heights_.cend() - 1};
        heightLeft < heightRight;
    ) {
        auto const side2{
            *heightLeft <= *heightRight ? *heightLeft++ : *heightRight--
        };
        auto const currVolume{side1-- * side2};
        maxVolume = std::max(maxVolume, currVolume);
    }
    return maxVolume;
}
