// problem : https://leetcode.com/problems/count-number-of-bad-pairs/description/
// submission : https://leetcode.com/problems/count-number-of-bad-pairs/submissions/1538434561
// solution post : https://leetcode.com/problems/count-number-of-bad-pairs/solutions/6404403/
//     c-modern-readable-code-optimal-time-comp-kah6

// #include <algorithm>
// #include <vector>
// #include <unordered_map>

// let 'n' be a length of the given array
// time complexity O(n)
// space complexity O(n)
// runtime 61 ms, beats 82.28 %
class Solution {
public:
    long long int countBadPairs(std::vector<int> const & nums) const;
private:
    class DiffsCounter{
    public:
        void operator()(int const);
        explicit DiffsCounter(std::unordered_map<int, size_t> & diffToCount);
    private:  
        size_t idx;
        std::unordered_map<int, size_t> & diffToCount;
    };
    class GoodPairsCounter{
    public:
        void operator()(std::pair<int, size_t> const & diffToCount);
        explicit GoodPairsCounter(size_t &);
    private:
        size_t & goodPairsCount;
    };
};

long long int Solution::countBadPairs(std::vector<int> const & nums) const {
    if(nums.size() == 1) {
        return 0;
    }
    auto diffToCount{std::unordered_map<int, size_t>{}};
    std::for_each(nums.begin(), nums.end(), DiffsCounter{diffToCount}); 
    auto const totalPairsCount{nums.size() * (nums.size() - 1) / 2};
    auto goodPairsCount{size_t{0}};
    std::for_each(diffToCount.cbegin(), diffToCount.cend(),
        GoodPairsCounter{goodPairsCount});
    return totalPairsCount - goodPairsCount;
}

void Solution::DiffsCounter::operator()(int const num) {
    ++diffToCount[idx++ - num];
}
Solution::DiffsCounter::DiffsCounter(
    std::unordered_map<int, size_t> & diffToCount
):
    idx{0},
    diffToCount{diffToCount}
{}

void Solution::GoodPairsCounter::operator()(
    std::pair<int, size_t> const & diffToCount
) {
    auto const count{diffToCount.second};
    if(count > 1) {
        goodPairsCount += count * (count - 1) / 2;
    }
}

Solution::GoodPairsCounter::GoodPairsCounter(size_t & goodPairsCount):
    goodPairsCount{goodPairsCount}
{}
