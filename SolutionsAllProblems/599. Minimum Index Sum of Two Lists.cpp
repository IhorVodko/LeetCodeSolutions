// problem : https://leetcode.com/problems/minimum-index-sum-of-two-lists/description/
// submission : https://leetcode.com/problems/minimum-index-sum-of-two-lists/submissions/1487358706
// solution post : https://leetcode.com/problems/minimum-index-sum-of-two-lists/solutions/6182136/c-modern-readable-code-beats-99-runtime-b9a68


// #include <string>
// #include <vector>
// #include <unordered_set>

struct ItWrapper{
    using T = std::vector<std::string>::const_iterator;
    bool operator==(ItWrapper const & other) const {
        return hasher(*it) == hasher(*other.it);
    }
    explicit ItWrapper(T const it) :
        it{it} 
    {}
    T it;
    auto static constexpr hasher{std::hash<std::string>{}};
};

template<>
struct std::hash<::ItWrapper> {
    size_t operator()(::ItWrapper const & key) const {
        return hasher(*key.it);
    }
    auto static constexpr hasher{std::hash<std::string>{}};
};

class Solution {
public:
    // let 'l1' be a parameter 'list1' length
    // 'l2' - a parameter 'list2' lenght
    // time complexity O(l1 + l2)
    // space complexity O(l1)
    // runtime 7 ms, beats 98.78 %
    std::vector<std::string> findRestaurant(
        std::vector<std::string> const & list1,
        std::vector<std::string> const & list2
    ) {
        using ItT = std::vector<std::string>::const_iterator;
        auto list1Set{std::unordered_set<::ItWrapper>{}};
        for(auto str{list1.cbegin()}, end{list1.cend()}; str < end; ++str) {
            list1Set.emplace(::ItWrapper{str});
        }
        auto indxSumToStrs{std::pair<size_t, std::vector<ItT>>{}};
        auto found{list1Set.cend()};
        auto const notFound{list1Set.cend()};
        auto sum{std::numeric_limits<int>::max()};
        auto minSum{std::numeric_limits<int>::max()};
        for(auto str{list2.cbegin()}, end{list2.cend()}; str < end; ++str) {
            found = list1Set.find(::ItWrapper{str});
            if(found == notFound) {
                continue;
            }
            sum = (str - list2.cbegin()) + (found->it - list1.cbegin());
            if(sum == minSum) {
                indxSumToStrs.second.emplace_back(str);
            } else if (sum < minSum) {
                indxSumToStrs.second.assign({str});
                minSum = sum;
            }
        }
        auto result{std::vector<std::string>{}};
        result.reserve(indxSumToStrs.second.size());
        for(auto const itStr: indxSumToStrs.second) {
            result.emplace_back(*itStr);
        }
        return result;
    }
};
