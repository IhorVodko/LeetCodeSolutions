// problem : https://leetcode.com/problems/rotate-string/description
// submission : https://leetcode.com/problems/rotate-string/submissions/1994216717
// solution post : https://leetcode.com/problems/rotate-string/solutions/8133791/c-modern-readable-code-beats-100-runtime-jrwb

// Approach : String Concatenation & Substring Search
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the target string length
// complexity :  O(n^2)
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
    auto rotateString(
        std::string_view const source_, 
        std::string_view const target_
    ) const -> bool;
};

auto Solution::rotateString(
    std::string_view const source_, 
    std::string_view const target_
) const -> bool {
    if(source_.size() != target_.size()) {
        return false;
    }

    // Concatenate two source strings to simulate rotation logic
    auto searchRng{std::string{}};
    
    searchRng.reserve(source_.size() * 2);
    searchRng.append(source_);
    searchRng.append(source_);

    auto const isAchivable{searchRng.find(target_) != std::string::npos};

    return isAchivable;
}
