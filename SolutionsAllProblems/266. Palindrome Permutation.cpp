// problem : https://leetcode.com/problems/palindrome-permutation/description/
// submission : https://leetcode.com/problems/palindrome-permutation/submissions/1574300447
// solution post : https://leetcode.com/problems/palindrome-permutation/solutions/6538603/
//     c-modern-readable-code-beats-100-runtime-9aag

// #include <algorithm>
// #include <functional>

// let 'n' be a length of the given string
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    bool canPermutePalindrome(std::string const & str_);
private:
    using MapT = std::unordered_map<char, size_t>;
    MapT chrToCount;
    std::function<void(char const chr)> countChrs{[&] (char const chr) {
        ++chrToCount[chr];
    }};
    std::function<bool(MapT::value_type const & count)> isUnevenCount{[]
        (MapT::value_type const & chrAndCount) {
            return chrAndCount.second % 2 == 1;
    }};
};


bool Solution::canPermutePalindrome(std::string const & str_) {
    chrToCount.clear();
    std::for_each(str_.begin(), str_.end(), countChrs);
    auto const unevenChrCountsCount{std::count_if(chrToCount.cbegin(),
        chrToCount.cend(), isUnevenCount)};
    return str_.size() % 2 == 1 ? unevenChrCountsCount == 1 :
        unevenChrCountsCount == 0;
}
