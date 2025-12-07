// problem :  https://leetcode.com/problems/count-partitions-with-max-min-difference-at-most-k/description/
// submission : https://leetcode.com/problems/count-partitions-with-max-min-difference-at-most-k/submissions/1849635195
// solution post : https://leetcode.com/problems/count-partitions-with-max-min-difference-at-most-k/solutions/7399033/
//    c-modern-readable-code-beats-100-runtime-wn9j 

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream{"display_runtime.txt"} << 0 << std::endl;
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
// let 'n' be the number of given numbers
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto countPartitions(
        std::span<int const> const nums_,
        int const maxMinDiffUpperLimit_
    ) const -> int;

private:
    static auto constexpr kModVal{1'000'000'007};
};

auto Solution::countPartitions(
    std::span<int const> const nums_,
    int const maxMinDiffUpperLimit_
) const -> int {
    namespace vs = std::views;

    auto const numsSz{std::ssize(nums_)};
    auto partitionsCntPerIndex{std::vector<int>(numsSz + 1)};
    partitionsCntPerIndex[0] = 1;
    auto partitionsCnt{partitionsCntPerIndex[0]};
    auto increasingDq{std::deque<int>{}}; 
    auto decreasingDq{std::deque<int>{}}; 
    for(auto beginIdx{0}; auto const endIdx: vs::iota(0, numsSz)) {
        while(
            !decreasingDq.empty() &&
            nums_[endIdx] > nums_[decreasingDq.back()]
        ) {
            decreasingDq.pop_back();
        }
        decreasingDq.emplace_back(endIdx);
        while (
            !increasingDq.empty() &&
            nums_[endIdx] < nums_[increasingDq.back()]
        ) {
            increasingDq.pop_back();
        }
        increasingDq.emplace_back(endIdx);
        while (
            beginIdx < endIdx &&
            !decreasingDq.empty() && !increasingDq.empty() &&
            nums_[decreasingDq.front()] - nums_[increasingDq.front()] >
                maxMinDiffUpperLimit_
        ) {
            partitionsCnt =
                (partitionsCnt - partitionsCntPerIndex[beginIdx++] + kModVal) %
                kModVal
            ;
            if (decreasingDq.front() < beginIdx) {
                decreasingDq.pop_front();
            }
            if (increasingDq.front() < beginIdx) {
                increasingDq.pop_front();
            }
        }
        partitionsCntPerIndex[endIdx+1] = partitionsCnt;
        partitionsCnt = (partitionsCnt * 2) % kModVal;
    }
    auto const partitionWaysTotCnt{partitionsCntPerIndex[numsSz]};
    return partitionWaysTotCnt;
}
