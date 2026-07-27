// problem : https://leetcode.com/problems/maximum-product-of-two-elements-in-an-array/description
// submission : https://leetcode.com/problems/maximum-product-of-two-elements-in-an-array/submissions/2083830438
// solution post : https://leetcode.com/problems/maximum-product-of-two-elements-in-an-array/solutions/8424667/
//    simplanation-simple-explanation-by-cyber-enqa/

// Approach : Single Pass Two Largest Elements Tracking
// Runtime : 0 ms, beats 100.00 %

// Complexity analysis
// let 'n' be the number of elements
// Time :  O(n)
// Space : O(1)

// import std;

namespace {

namespace rs = std::ranges;

// Holds the two largest elements encountered.
struct Maxima {
    int first{};
    int second{};
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
    static auto maxProduct(std::vector<int> const & nums_) -> int;
};

auto Solution::maxProduct(std::vector<int> const & nums_) -> int {

    // Evaluates and updates the current top two maximums.
    auto const updateMaxima{[] (auto maxima_, auto const num_) {
        auto & [maxFirst, maxSecond]{maxima_};

        if(num_ > maxFirst) {
            maxSecond = std::exchange(maxFirst, num_);
        } else {
            maxSecond = std::max(maxSecond, num_);
        }

        return maxima_;
    }};

    // Reduces the array to its two largest values in a single pass.
    auto const [maxFirst, maxSecond]{rs::fold_left(nums_, Maxima{}, updateMaxima)};

    return (maxFirst - 1) * (maxSecond - 1);
}
