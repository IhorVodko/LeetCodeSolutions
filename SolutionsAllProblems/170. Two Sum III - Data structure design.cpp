// problem : https://leetcode.com/problems/two-sum-iii-data-structure-design/description/
// submission : https://leetcode.com/problems/two-sum-iii-data-structure-design/submissions/1503380050
// solution post : https://leetcode.com/problems/two-sum-iii-data-structure-design/solutions/6257204/c-modern-readable-code-optimal-time-comp-a3fl

// #include <algorithm>
// #include <unordered_map>

// let 'n' be a count of unique numbers in input
// time complexity O(n)
// space complexity O(n)
// runtime 67 ms, beats 71.61 %
class TwoSum {
public:
    void add(int const number) {
        ++numCounts[number];
    }
    bool find(int const value) const {
        auto pred{[&] (auto const & numCount) {
            auto complement = static_cast<long long>(value) - numCount.first;
            if(numCounts.contains(complement)) {
                if(complement != numCount.first || numCount.second >= 2) {
                    return true;
                }
            }
            return false;
        }};
        return std::any_of(numCounts.cbegin(), numCounts.cend(), pred);
    }
    TwoSum() {}
private:
    std::unordered_map<long long, size_t> numCounts;
};

/**
 * Your TwoSum object will be instantiated and called as such:
 * TwoSum* obj = new TwoSum();
 * obj->add(number);
 * bool param_2 = obj->find(value);
 */
