// problem : https://leetcode.com/problems/count-servers-that-communicate/description/
// submission : https://leetcode.com/problems/count-servers-that-communicate/submissions/1518045029
// solution post : https://leetcode.com/problems/count-servers-that-communicate/solutions/6320249/c-modern-readable-code-beats-100-runtime-ovs9

// #include <limits>
// #include <vector>

// let 'l' be a parameter 'grid' length
// 'w' - width
// time complexity O(l * w)
// space complexity O(l + w)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using Mx = std::vector<std::vector<int>>;
    int countServers(Mx const & grid) const {
        auto const rs{grid.size()};
        auto const cs{grid.at(0).size()};
        auto commServersCount{size_t{0}}; 
        auto serversInColsCounts{std::vector<size_t>(cs, 0)};
        auto colOfLastServerInRow{std::vector<size_t>(rs, max)};
        auto serversCountInRow{size_t{0}};
        for(auto r{size_t{0}}; r < rs; ++r) {
            serversCountInRow = 0;
            for(auto c{size_t{0}}; c < cs; ++c) {
                if(grid.at(r).at(c) == 1) {
                    ++serversCountInRow;
                    ++serversInColsCounts.at(c);
                    colOfLastServerInRow.at(r) = c;
                }
            }
            if(serversCountInRow >= 2) {
                commServersCount += serversCountInRow;
                colOfLastServerInRow.at(r) = max;
            }
        }
        for(auto r{size_t{0}}; r < rs; ++r) {
            if(colOfLastServerInRow.at(r) != max &&
                serversInColsCounts.at(colOfLastServerInRow.at(r)) >= 2
            ) {
                ++commServersCount;
            }
        }
        return commServersCount;
    }
private:
    size_t max{std::numeric_limits<size_t>::max()};
};
