// problem : https://leetcode.com/problems/maximum-count-of-positive-integer-and-negative-integer/description/
// submission : https://leetcode.com/problems/maximum-count-of-positive-integer-and-negative-integer/submissions/
//     1571760271
// solution post : https://leetcode.com/problems/maximum-count-of-positive-integer-and-negative-integer/solutions/6530299/
//     c-modern-readable-code-beats-100-runtime-p1uo

// #include <algorithm>
// #include <vector>

// let 'n' be a length of the given array
// time complexity O(log(n))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    int maximumCount(std::vector<int> const & nums_) const;
private:
    using ItcT = std::vector<int>::const_iterator;
    ItcT FindLowerBound(
        ItcT first,
        ItcT const end 
    ) const;
    ItcT FindUpperBound(
        ItcT first,
        ItcT const end
    ) const;
};

int Solution::maximumCount(std::vector<int> const & nums_) const {
    auto const negCount{FindLowerBound(nums_.begin(), nums_.end()) -
        nums_.begin()};
    auto const posCount{nums_.end() - FindUpperBound(nums_.begin(),
        nums_.end())};
    return std::max(negCount, posCount);
}

Solution::ItcT Solution::FindLowerBound(
    ItcT first,
    ItcT const end
) const {
    auto last{end - 1};
    auto lowerBound{end};
    for(;first <= last;) {
        auto mid{first + (last - first) / 2};
        if(*mid < 0) {
            first = mid + 1;
        } else if(*mid >= 0) {
            last = mid - 1;
            lowerBound = mid;
        }
    }
    return lowerBound;
}

Solution::ItcT Solution::FindUpperBound(
    ItcT first,
    ItcT const end
) const {
    auto last{end - 1};
    auto upperBound{end};
    for(;first <= last;) {
        auto mid{first + (last - first) / 2};
        if(*mid <= 0) {
            first = mid + 1;
        } else if(*mid > 0) {
            last = mid - 1;
            upperBound = mid;
        }
    }
    return upperBound;
}


// for educational purposes no stl algos are used
// let 'n' and 'm' be a given matrix dimensions
