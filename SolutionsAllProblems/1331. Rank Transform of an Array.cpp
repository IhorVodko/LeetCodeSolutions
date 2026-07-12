// problem : https://leetcode.com/problems/rank-transform-of-an-array/description
// submission : https://leetcode.com/problems/rank-transform-of-an-array/submissions/2065068410
// solution post : https://leetcode.com/problems/rank-transform-of-an-array/solutions/8392523/
//    modern-readable-code-optimal-time-comple-y5z8

// Approach : Sort and Chunk by Value
// Runtime : 22 ms, beats 96.83 %

// Complexity analysis
// let 'n' be the count of numbers
// Time :  O(n * log(n))
// Space : O(n)

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

auto constexpr kMinNum{std::numeric_limits<int>::min()};

// Binds values to original positions.
struct numData final {
    int num{};
    int origIdx{};
};

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace 

class Solution final {
public:
    [[nodiscard]]
    static auto arrayRankTransform(std::vector<int> & nums_) -> std::vector<int>;
};

auto Solution::arrayRankTransform(std::vector<int> & nums_) -> std::vector<int> {
    // Attach indices to preserve original array locations.
    auto numAndIdxSorted{
        nums_ |
        vs::enumerate |
        vs::transform([] (auto const & numAndIdx_) {
            auto const [origIdx, num]{numAndIdx_};
            return numData{num, static_cast<int>(origIdx)};
        }) |
        rs::to<std::vector>()
    };

    // Order by value to process ranks ascendingly.
    rs::sort(numAndIdxSorted, {}, &numData::num);

    // Group identical numbers so they share the same rank.
    auto chunks{
        numAndIdxSorted |
        vs::chunk_by([] (auto const & lhs_, auto const & rhs_) {
            return lhs_.num == rhs_.num;
        })
    };

    // Overwrite original array with computed ranks based on chunk index.
    for(auto const [idx, chunk]: chunks | vs::enumerate) {
        auto const rank{static_cast<int>(idx) + 1};
        for(auto const origIdx: chunk | vs::transform(&numData::origIdx)) {
            nums_[origIdx] = rank;
        }
    }

    return nums_;
}
