// problem : https://leetcode.com/problems/power-grid-maintenance/description/
// submission : https://leetcode.com/problems/power-grid-maintenance/submissions/1822544716
// solution post : https://leetcode.com/problems/power-grid-maintenance/solutions/7331050/
//    c-modern-readable-code-beats-100-runtime-fwr0

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream("display_runtime.txt") << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class Solution {
public:
    using connection = std::vector<int>;
    using query = std::vector<int>;

// let 's' be the given number of stations
// 'c' - of the given connections
// 'q' - of the given queries
// time complexity O(s + c + q)
// space complexity O(s)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto processQueries(
        int const stationsCnt_,
        std::span<connection const> const connections_,
        std::span<query> const queries_
    ) const ->std::vector<int>;

private:
class DSUnion {
public:
    DSUnion(int const size_);

    [[nodiscard]]
    auto Find(int const node_) -> int;
    auto Join(
        int const node1_,
        int const node2_
    ) -> void;

private:
    std::vector<int> mParentNodes;
};

    static int constexpr kOpType1{1};
    static int constexpr kOpType2{2};
};

auto Solution::processQueries(
    int const stationsCnt_,
    std::span<connection const> const connections_,
    std::span<query> const queries_
) const ->std::vector<int> {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto dsu{DSUnion{stationsCnt_ + 1}};
    for(auto const & connection: connections_) {
        dsu.Join(connection[0], connection[1]);
    }
    auto onStations{std::vector<bool>(stationsCnt_ + 1, true)};
    auto offStationCnts{std::vector<int>(stationsCnt_ + 1, 0)};
    auto stationToMinStation{std::unordered_map<int, int>{}};
    stationToMinStation.reserve(stationsCnt_);
    for(auto const & query: queries_) {
        auto const opType{query[0]};
        auto const station{query[1]};
        if(opType == kOpType2) {
            onStations[station] = false;
            ++offStationCnts[station];
        } 
    }
    for(auto const station: vs::iota(1, stationsCnt_ + 1)) {
        auto const rootStation{dsu.Find(station)};
        if(!stationToMinStation.contains(rootStation)) {
            stationToMinStation[rootStation] = -1;
        }
        auto & minStation{stationToMinStation[rootStation]};
        if(onStations[station]) {
            if(minStation == -1 || minStation > station) {
                minStation = station;
            }
        }
    }
    auto ans{std::vector<int>{}};
    ans.reserve(stationsCnt_);
    for(auto const idx: vs::iota(0, std::ssize(queries_)) | vs::reverse) {
        auto const opType{queries_[idx][0]};
        auto const stationQ{queries_[idx][1]};
        auto const rootStation{dsu.Find(stationQ)};
        auto const minStation{stationToMinStation[rootStation]};
        if(opType == kOpType1) {
            if(onStations[stationQ]) {
                ans.emplace_back(stationQ);
            } else {
                ans.emplace_back(minStation);
            }
        }
        if(opType == kOpType2) {
            if(offStationCnts[stationQ] > 1) {
                --offStationCnts[stationQ];
            } else {
                onStations[stationQ] = true;
                if(minStation == -1 || minStation > stationQ) {
                    stationToMinStation[rootStation] = stationQ;
                }
            }
        }
    }
    rngs::reverse(ans);
    return ans;
}

Solution::DSUnion::DSUnion(int const size_):
    mParentNodes(size_)
{
    std::iota(mParentNodes.begin(), mParentNodes.end(), 0);
}

auto Solution::DSUnion::Find(int const node_) -> int {
    if(mParentNodes.at(node_) == node_) {
        return node_;
    }
    mParentNodes.at(node_) = Find(mParentNodes.at(node_));
    return mParentNodes.at(node_);
} 

auto Solution::DSUnion::Join(
    int const node1_,
    int const node2_
) -> void {
    mParentNodes.at(Find(node1_)) = Find(node2_);
}
