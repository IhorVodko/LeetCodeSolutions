// problem : https://leetcode.com/problems/rotate-image/description/
// submission : https://leetcode.com/problems/rotate-image/submissions/1995771527
// solution post : https://leetcode.com/problems/rotate-image/solutions/8145695/c-modern-readable-code-beats-100-runtime-w0hr

// Approach : Transpose and Reverse
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the matrix size
// complexity :  O(n^2)
// complexity : O(1)

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
    using arr2d = std::vector<std::vector<int>>;

    auto rotate(arr2d & mx_) const noexcept -> void;

private:
    auto Transpose(arr2d & mx_) const noexcept -> void;
    auto ReflectVertical(arr2d & mx_) const noexcept -> void;
};

auto Solution::rotate(arr2d & mx_) const noexcept -> void {
    // Rotation 90 degrees clockwise is equivalent to the combination of transposition
    // (swap rows with columns) and vertical reflection (reverse each row)
    Transpose(mx_);
    ReflectVertical(mx_);
}

auto Solution::Transpose(arr2d & mx_) const noexcept -> void {
    namespace vs = std::views;

    auto const rcSz{mx_.size()};

    for(auto const r: vs::iota(0u, rcSz)) {
        for(auto const c: vs::iota(r + 1, rcSz)) {
            std::swap(mx_[r][c], mx_[c][r]);
        }
    }
}

auto Solution::ReflectVertical(arr2d & mx_) const noexcept -> void {
    namespace rngs = std::ranges;

    for(auto & row: mx_) {
        rngs::reverse(row);
    }
}
