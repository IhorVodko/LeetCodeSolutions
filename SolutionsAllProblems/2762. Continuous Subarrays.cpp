// problem : https://leetcode.com/problems/continuous-subarrays/description/
// submission : https://leetcode.com/problems/continuous-subarrays/submissions/1478797329
// solution post : https://leetcode.com/problems/continuous-subarrays/solutions/6147040/c-modern-readable-code-by-cyberartist-ti5f


// #include <deque>
// #include <iterator>
// #include <vector>


class Solution {
public:
    // let 'n' be a parameter 'nums' length
    // time complexity O(n)
    // space complexity O(n)
    // runtime 79 ms, beats 93.11 %
    long long continuousSubarrays(std::vector<int> const & nums) {
        using itT = std::remove_cvref<decltype(nums)>::type::const_iterator;
        auto qMin{std::deque<itT>{}};
        auto qMax{std::deque<itT>{}};
        auto count{0LL};
        auto constexpr limit{2};
        for(auto first{nums.cbegin()}, last{nums.cbegin()}, end{nums.cend()};
            last < end; ++last
        ) {
            while(!qMin.empty() && *qMin.back() >= *last) {
                qMin.pop_back();
            }
            qMin.push_back(last);
            while(!qMax.empty() && *qMax.back() <= *last) {
                qMax.pop_back();
            }
            qMax.push_back(last);
            while(!qMin.empty() && !qMax.empty() &&
                *qMax.front() - *qMin.front() > limit
            ) {
                if(qMin.front() < qMax.front()) {
                    first = qMin.front();
                    qMin.pop_front();
                } else {
                    first = qMax.front();
                    qMax.pop_front();
                }
                ++first;
            } 
            count += std::distance(first, last) + 1;
        }
        return count;
    }
};
