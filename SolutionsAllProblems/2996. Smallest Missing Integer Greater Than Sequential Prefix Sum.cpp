// problem : https://leetcode.com/problems/smallest-missing-integer-greater-than-sequential-prefix-sum/description
// submission : https://leetcode.com/problems/smallest-missing-integer-greater-than-sequential-prefix-sum/submissions/2103328406
// solution post : https://leetcode.com/problems/smallest-missing-integer-greater-than-sequential-prefix-sum/solutions/8455476/
//    simplanation-simple-explanation-by-cyber-f0ol

// Approach : Arithmetic Progression Sum & Fast Lookup
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the count of numbers
// Time :  O(n)
// Space : O(1) auxiliary space

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

auto constexpr kMaxNum{50};
auto constexpr kMaxseqSum{kMaxNum * (kMaxNum + 1) / 2};

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
    static auto missingInteger(std::vector<int> const & nums_) -> int;
};

auto Solution::missingInteger(std::vector<int> const & nums_) -> int {
    // 1. Locate the first pair of elements breaking the sequential prefix
    auto seqBreak{rs::adjacent_find(
        nums_,
        [] (auto const curr_, auto const next_) {
            return curr_ + 1 !=  next_;
        }
    )};

    // 2. Fallback to the last element if the entire array is sequential
    if(seqBreak == nums_.end()) {
        seqBreak = rs::prev(seqBreak);
    }

    // 3. Compute the sum of the sequential prefix
    auto const seqLen{std::distance(nums_.begin(), seqBreak) + 1};
    auto const seqSum{(nums_.front() + *seqBreak) * seqLen / 2};

    // 4. Record all array values for constant-time presence checks
    auto presentNumsLookup{std::bitset<kMaxseqSum + 1>{}};
    for(auto const num: nums_) {
        presentNumsLookup.set(num);
    }

    // Evaluates if an integer is absent from the input array
    auto const isMissing{[&] (auto const num_) {
        return !presentNumsLookup.test(num_);
    }};

    // 5. Find the smallest missing integer greater than or equal to the sum
    return *rs::find_if(vs::iota(seqSum), isMissing);
}
