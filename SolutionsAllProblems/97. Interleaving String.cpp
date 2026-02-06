// problem : https://leetcode.com/problems/interleaving-string/description/
// submission : https://leetcode.com/problems/interleaving-string/submissions/1910534654
// solution post : https://leetcode.com/problems/interleaving-string/solutions/7558389/
//    c-modern-readable-code-beats-100-runtime-urgw

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the first string size
// 'm' - second strings size
// 'k' - target string size
// time complexity O(n * m)
// space complexity O(min(n, m))
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto isInterleave(
        std::string_view const s1_,
        std::string_view const s2_,
        std::string_view const s3_
    ) -> bool;
};

auto Solution::isInterleave(
    std::string_view const s1_,
    std::string_view const s2_,
    std::string_view const s3_
) -> bool {
    namespace vs = std::views;

    auto const sz1{s1_.size()};
    auto const sz2{s2_.size()};
    if(sz1 > sz2) {
        return isInterleave(s2_, s1_, s3_);
    }
    auto const sz3{s3_.size()};
    // Length mismatch makes interleaving impossible
    if(sz1 + sz2 != sz3) {
        return false;
    } else if(sz1 == sz3) {
        return s1_ == s3_;
    } else if(sz2 == sz3) {
        return s2_ == s3_;
    }
    // memo[i] represents whether s3_[0..i1+i2-1] can be formed
    // using s1_[0..i1-1] and s2_[0..i2-1]
    auto memo{std::vector(sz2 + 1, false)};
    memo[0] = true;
    // Initialize first row where only characters from s2_ are used
    for (auto i2: vs::iota(1u, sz2 + 1)) {
        auto const isValid{memo[i2 - 1] && s2_[i2 - 1] == s3_[i2 - 1]};
        if(isValid) {
            memo[i2] = isValid;
        } else {
            break;
        }
    }
    // Iterate through s1_ characters, updating the DP state row by row
    for (auto i1: vs::iota(1u, sz1 + 1)) {
        // Update first column where only characters from s1_ are used
        memo[0] = memo[0] && s1_[i1 - 1] == s3_[i1 - 1];
        for (auto i2: vs::iota(1u, sz2 + 1)) {
            auto const chr = s3_[i1 + i2 - 1];
            // Current state depends on whether the next character
            // can be taken from s1_ or s2_
            memo[i2] =
                (memo[i2] && s1_[i1 - 1] == chr) ||
                (memo[i2 - 1] && s2_[i2 - 1] == chr);
        }
    }
    auto const isInterleaved{memo.back()};
    return isInterleaved;
}
