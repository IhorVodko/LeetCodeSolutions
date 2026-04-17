// problem : https://leetcode.com/problems/minimum-absolute-distance-between-mirror-pairs/description
// submission : https://leetcode.com/problems/minimum-absolute-distance-between-mirror-pairs/submissions/1981160415
// solution post : https://leetcode.com/problems/minimum-absolute-distance-between-mirror-pairs/solutions/7968148/
//    c-modern-readable-code-beats-9926-runtim-679u

// Approach :
// Runtime : 81 ms, beats 99.26 %

// Complexity
// let 'n' be the length of the array of numbers
// complexity :  O(n)
// complexity : O(n)

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

class Solution final {
public:
    [[nodiscard]]
    auto minMirrorPairDistance(std::vector<int> const & nums_) const -> int;

private:
    [[nodiscard]]
    // Helper method to reverse the digits of a number, Leading zeros are omitted after
    // reversing
    inline auto RevNum(int num_) const noexcept -> int;  

    static auto constexpr kMaxDist{std::numeric_limits<int>::max()};
    // Base 10 multiplier used for digit extraction and rebuilding
    static auto constexpr kRadix{10};
};

auto Solution::minMirrorPairDistance(std::vector<int> const & nums_) const -> int {
    namespace vs = std::views;

    auto const numsSz{static_cast<int>(nums_.size())};
    auto minDist{kMaxDist};

    // Hash map to store the closest seen index of each value
    auto numToRecentIdx{std::unordered_map<int, int>{}};
    numToRecentIdx.reserve(numsSz * 2);

    for(auto const numIdx: vs::iota(0, numsSz) | vs::reverse) {
        // Search the map for the mirror complement on the right
        if(auto const numAndRecentIdxIt{numToRecentIdx.find(RevNum(nums_[numIdx]))};
            numAndRecentIdxIt != numToRecentIdx.end()
        ) {
            auto currDist{numAndRecentIdxIt->second - numIdx};
            minDist = std::min(minDist, currDist);
        }

        // Record the current number and its index for future leftward elements
        numToRecentIdx[nums_[numIdx]] = numIdx;
    }

    return minDist == kMaxDist ? -1 : minDist;
}

auto Solution::RevNum(int num_) const noexcept -> int {
    // Variable to accumulate the reversed digits
    auto revNum{0};

    // Continue looping until all digits are extracted
    while(num_ > 0) {
        // Extract both quotient and remainder in a single operation
        auto const [nextNum, digit]{std::div(num_, kRadix)};
        
        // Shift the accumulated result left by base 10 and add the new digit
        revNum = revNum * kRadix + digit;
        // Update the number to the remaining left-side digits
        num_ = nextNum;
    }

    return revNum;
}
