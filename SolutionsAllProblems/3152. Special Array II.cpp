// problem : https://leetcode.com/problems/special-array-ii/description/
// submission : https://leetcode.com/problems/special-array-ii/submissions/1474699485
// solution post : https://leetcode.com/problems/special-array-ii/solutions/6130469/c-modern-readable-code


// #include <vector>


class Solution {
public:
    // let 'n' be a 'nums' length,
    //   'm' - a 'queries' length
    // time complexity O(n + m)
    // space complexity O(n)
    // runtime 7 ms, beats 73.70 %
    std::vector<bool> isArraySpecial(
        std::vector<int> & nums,
        std::vector<std::vector<int>> const & queries
    ) {
        prefixSum.reserve(nums.size());
        prefixSum.emplace_back(0);
        for(auto idx{size_t(1)}; idx < nums.size(); ++idx) {
            prefixSum.emplace_back(
                prefixSum.back() +
                isSameParity(nums.at(idx), nums.at(idx - 1)) 
            );
        }
        result.reserve(queries.size());
        for(auto const & querie: queries) {
            result.emplace_back(prefixSum.at(querie.front()) -
                prefixSum.at(querie.back()) == 0);
        }
        return result;
    }
private:
    bool isSameParity(
        int const num1,
        int const num2
    ) const {
        return (num1 - num2) % 2 == 0;
    }
    std::vector<size_t> prefixSum;
    std::vector<bool> result;
};
