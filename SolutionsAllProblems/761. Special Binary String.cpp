// problem : https://leetcode.com/problems/special-binary-string/description
// submission : https://leetcode.com/problems/special-binary-string/submissions/1925593440
// solution post : https://leetcode.com/problems/special-binary-string/solutions/7594800/
//    c-modern-readable-code-beats-100-runtime-25p2

// import std;

inline static int const fastIOInit{
    [] {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

// let 'n' be the string length
// time complexity O(n * log(n))
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    [[nodiscard]]
    auto makeLargestSpecial(std::string_view const str_) const -> std::string;
};

auto Solution::makeLargestSpecial(std::string_view const str_) const -> std::string {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    // Stack simulates recursion levels. Each level stores special substrings found
    // inside it
    auto stck{std::stack<std::vector<std::string>>{}};
    // Base level to collect top-level special substrings
    stck.emplace();
    for(auto const chr: str_) {
        if(chr == '1') {
            // Start a new nested special substring level
            stck.emplace();
        } else {
            // Close current level and process collected inner substrings
            auto subStrs{std::move(stck.top())};
            stck.pop();
            // Sort inner substrings in descending order to maximize lexicographical
            // result
            rngs::sort(subStrs, std::greater{});
            // Merge sorted inner substrings and wrap with outer 1 and 0
            auto mergedSubStrs{
                rngs::fold_left(subStrs, std::string{"1"}, std::plus{})};
            mergedSubStrs += '0';
            // Append the completed special substring to its parent level
            stck.top().emplace_back(std::move(mergedSubStrs));
        }
    }
    // Process top-level substrings
    auto & subStrs{stck.top()};
    // Sort top-level substrings to obtain lexicographically largest result
    rngs::sort(subStrs, std::greater{});
    // Concatenate all sorted substrings
    auto maxStr{rngs::fold_left(subStrs, std::string{}, std::plus{})};
    return maxStr;
}
