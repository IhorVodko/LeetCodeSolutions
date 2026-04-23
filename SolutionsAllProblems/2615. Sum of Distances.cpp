// problem : https://leetcode.com/problems/sum-of-distances/description
// submission : https://leetcode.com/problems/sum-of-distances/submissions/1986209526
// solution post : https://leetcode.com/problems/sum-of-distances/solutions/8077179/
//    c-modern-readable-code-beats-100-runtime-n62z

// Approach : Prefix and Suffix Sums on Grouped Indices
// Runtime : 34 ms, beats 99.25 %

// Complexity
// let 'n' be the count of numbers
// complexity :  O(n * log(n))
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

// Struct to store a number alongside its original array index
struct NumAndIdx final {
    int mNum{};
    long long mIdx{};
};

class Solution final {
public:
    using ll = long long;

    [[nodiscard]]
    auto distance(std::vector<int> const & nums_) const -> std::vector<ll>;
};

auto Solution::distance(std::vector<int> const & nums_) const -> std::vector<ll> {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const numsSz{std::ssize(nums_)};

    auto numAndIdxArr{std::vector<NumAndIdx>{}};

    numAndIdxArr.reserve(numsSz);

    for(auto const j: vs::iota(0, numsSz)) {
        numAndIdxArr.emplace_back(nums_[j], j);
    }

    // Sort the mapped elements primarily by number, then by index
    rngs::sort(numAndIdxArr, [] (auto const & lNumAndIdx_, auto const & rNumAndIdx_) {
        auto const [lNum, lIdx]{lNumAndIdx_};
        auto const [rNum, rIdx]{rNumAndIdx_};
        if(lNum == rNum) {
            return lIdx < rIdx;
        }
        return lNum < rNum;
    });

    // Vector to store the final computed distances for each element
    auto sums{std::vector<ll>(numsSz)};

    // Traverse the sorted array to process chunks of identical numbers
    for(auto itB{numAndIdxArr.cbegin()}, itE{numAndIdxArr.cbegin()};
        itB != numAndIdxArr.cend(); itB = itE
    ) {
        // Variable to accumulate the sum of indices yet to be processed
        auto postSum{0ll};

        // Advance end iterator to find the boundaries of the identical group
        while(itE != numAndIdxArr.cend() && itB->mNum == itE->mNum) {
            postSum += (itE++)->mIdx;
        }
        
        // Variable to accumulate the sum of indices already processed
        auto prefSum{0ll};
        auto it{itB};

        // Iterate through the identified chunk of identical numbers
        while(it != itE) {
            // Variable to calculate the distance sum for the current index
            auto sum{0ll};
            // Number of identical elements processed before the current one
            auto const prefCnt{it - itB};
            // Number of identical elements including and after the current one
            auto const postCnt{itE - it};
            auto const idx{it->mIdx};

            // Calculate distance contribution from all previous occurrences
            sum += idx * prefCnt  - prefSum;  
            // Calculate distance contribution from all subsequent occurrences
            sum += postSum - idx * postCnt;
            sums[idx] = sum; 
            prefSum += idx;
            postSum -= idx;
            ++it;
        }
    }

    return sums;
}
