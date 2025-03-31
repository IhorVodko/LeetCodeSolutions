// problem : https://leetcode.com/problems/put-marbles-in-bags/description
// submission : https://leetcode.com/problems/put-marbles-in-bags/submissions/1592388794
// solution post : https://leetcode.com/problems/put-marbles-in-bags/solutions/6601134/
//     c-modern-readable-code-optimal-time-comp-qaeq

// #include <algorithm>
// #include <numeric>
// #include <vector>

// let 'n' be given marbles count
// time complexity O(n * log(n))
// space complexity O(n)
// runtime 31 ms, beats 89.03 %class 
Solution {
public:
    long long putMarbles(
        std::vector<int> const & weights_,
        int const bagsCount_
    ) const {
        auto const marblesCount{weights_.size()};
        auto adjacentWeightsSums{std::vector<int>{}};
        adjacentWeightsSums.reserve(marblesCount);
        std::adjacent_difference(weights_.begin(), weights_.end(),
            std::back_inserter(adjacentWeightsSums), std::plus{});
        if(marblesCount >= 2) {
            adjacentWeightsSums.erase(adjacentWeightsSums.begin());
        }
        std::sort(adjacentWeightsSums.begin(), adjacentWeightsSums.end());
        auto const maxMinDiff{std::inner_product(adjacentWeightsSums.crbegin(),
            adjacentWeightsSums.crbegin() + bagsCount_ - 1,
            adjacentWeightsSums.cbegin(), 0LL, std::plus{},
            std::minus{})};
        return maxMinDiff;
    }
};
