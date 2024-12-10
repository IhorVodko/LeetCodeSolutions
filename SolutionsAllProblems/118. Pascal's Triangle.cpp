// problem : https://leetcode.com/problems/pascals-triangle/description/
// submission : https://leetcode.com/problems/pascals-triangle/submissions/1475352565
// solution post : https://leetcode.com/problems/pascals-triangle/solutions/6133133/c-modern-readable-code-beats-100-runtime

// #include <algorithm>
// #include <vector>


class Solution {
public:
    // let 'n' be an input number
    // time complexity O(n^2)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    std::vector<std::vector<int>> generate(
        int numRows
    ) const {
        auto result{std::vector<std::vector<int>>{}};
        result.emplace_back(decltype(result)::value_type{1});
        result.reserve(numRows);
        auto rowSize{size_t{2}};
        while(--numRows > 0) {
            auto const & rowPrev{result.back()};
            auto row{std::vector<int>{}};
            row.reserve(rowSize++);
            row.emplace_back(1);
            std::transform(rowPrev.cbegin(), rowPrev.cend() - 1,
                rowPrev.cbegin() + 1, std::back_inserter(row), std::plus());
            row.emplace_back(1);
            result.emplace_back(row);
        }
        return result;
    }
};
