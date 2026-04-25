// problem : https://leetcode.com/problems/maximize-the-distance-between-points-on-a-square/description
// submission : https://leetcode.com/problems/maximize-the-distance-between-points-on-a-square/submissions/1987836003
// solution post : https://leetcode.com/problems/maximize-the-distance-between-points-on-a-square/solutions/8097238/
//    c-modern-readable-code-beats-9438-runtim-dho5

// Approach : Binary Search on the Answer with Greedy Validation
// Runtime :  7 ms, beats 94.38 %

// Complexity
// let 'n' be the number of points given
// 'm' - number of points to select
// 'k' - square side length
// complexity :  O(n * log(n) + n * m + log(k / m)) 
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
    using ll = long long;

    // Computes the maximum possible minimum distance between selectedPointsSz_ points.
    [[nodiscard]]
    auto maxDistance(
        // The length of the side of the square.
        int const side_,
        // The list of 2D coordinates representing the points.
        std::vector<std::vector<int>> const & points_,
        // The number of points to select.
        int const selectedPointsSz_
    // Returns an integer representing the maximum distance.
    ) -> int;

private:
    // Checks if a minimum distance of x is possible.
    [[nodiscard]]
    auto IsAchivable(ll const dist_) -> bool;

    // Stores 1D perimeter representations of points.
    std::vector<ll> mDists{};
    // Stores the next valid point index for a distance.
    std::vector<ll> mNextIdxs{};
    ll mPointsSz{};
    ll mSelectedPointsSz{};
    ll mPerimeter{};
};


auto Solution::maxDistance(
    int const side_,
    std::vector<std::vector<int>> const & points_,
    int const selectedPointsSz_
) -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    mPointsSz = std::ssize(points_);
    mSelectedPointsSz = selectedPointsSz_;
    mPerimeter = 4ll * side_;

    // Stores 1D perimeter representations of points.
    mDists.clear();
    mDists.reserve(mPointsSz);

    // Map 2D coordinates to a 1D distance along the perimeter.
    for(auto const & point: points_) {
        auto const x{point[0]};
        auto const y{point[1]};
        auto const dist{(x == 0 || y == side_) ? (mPerimeter - x - y) : (x + y)};

        mDists.emplace_back(dist);
    }

    rngs::sort(mDists);

    // Stores the next valid point index for a distance.
    mNextIdxs = std::vector<ll>(mPointsSz);

    // Do binary search for the maximum minimum distance between two points
    auto const distSearchSpace{vs::iota(1ll, mPerimeter / mSelectedPointsSz + 1)};
    auto const distIt{rngs::partition_point(distSearchSpace,
        [this] (auto const dist_) { return IsAchivable(dist_); } )};
    auto const maxMinDist{
        distIt == distSearchSpace.cbegin() ? 0ll : *rngs::prev(distIt)};

    return maxMinDist;
}

auto Solution::IsAchivable(ll const dist_) -> bool {
    namespace vs = std::views;

    auto const mPointsSz{std::ssize(mNextIdxs)};

    // Finds the next valid point for each start index.
    for(auto nextIdx{0}; auto const currIdx: vs::iota(0, mPointsSz)) {
        // Ensure the next pointer is strictly ahead of the current.
        nextIdx = std::max(nextIdx, currIdx + 1);

        // Advance pointer until distance gap is at least dist_.
        while(nextIdx < mPointsSz && mDists[nextIdx] - mDists[currIdx] < dist_) {
            ++nextIdx;
        }

        // Save the index of the next valid point.
        mNextIdxs[currIdx] = nextIdx;
    }    

    // Maximum starting coordinate to still allow mSelectedPointsSz points.
    auto const maxDist{
        mDists[mPointsSz - 1] + mPerimeter - (mSelectedPointsSz - 1) * dist_};
    // Maximum allowed distance gap without overlapping.
    auto const maxDistGap{mPerimeter - dist_};

    // Attempt starting the sequence from each valid point.
    for(auto i1{0}; i1 < mPointsSz && mDists[i1] <= maxDist; ++i1) {
        auto i2{i1};

        // Jump mSelectedPointsSz-1 times to collect the required points.
        for(auto i3{mSelectedPointsSz - 1}; i3 > 0 && i2 != mPointsSz; --i3) {
            // Move to the next valid point index.
            i2 = mNextIdxs[i2];
        }

        // Check if mSelectedPointsSz points were found without exceeding perimeter.
        if(i2 != mPointsSz && mDists[i2] - mDists[i1] <= maxDistGap) {
            // A valid configuration was successfully found.
            return true;
        }
    }

    // Distance dist_ is impossible to achieve with mSelectedPointsSz points.
    return false;
}
