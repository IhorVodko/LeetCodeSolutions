// problem : https://leetcode.com/problems/process-string-with-special-operations-i/description/
// submission : https://leetcode.com/problems/process-string-with-special-operations-i/submissions/2035291872
// solution post : https://leetcode.com/problems/process-string-with-special-operations-i/solutions/8338277/
//    c-modern-readable-code-beats-100-runtime-5rki

// Approach : Simulation - Linear Scan with String Accumulator
// Runtime : 0 ms, beats 100.00 %


// Complexity
// let 'n' be the given string length
// 'm' average length of the accumulated (output) string
// Time :  O(n * m)
// Space : O(1), auxiliary space

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto processStr(std::string_view const strIn_) -> std::string;

private:
    // Operation character mappings
    auto static constexpr kDeleteLast{'*'};
    auto static constexpr kDuplicate{'#'};
    auto static constexpr kReverse{'%'};
};

auto Solution::processStr(std::string_view const strIn_) -> std::string {
    namespace vs = std::views;
    namespace rs = std::ranges;

    assert(!strIn_.empty());

    auto strOut{""s};
    for(auto const chr: strIn_) {
        switch(chr) {
            case kDeleteLast:
                if(!strOut.empty()) {
                    strOut.pop_back();
                }
                break;
            case kDuplicate:
                strOut += strOut;
                break;
            case kReverse:
                rs::reverse(strOut);
                break;
            default:
                assert('a' <= chr && chr <= 'z');

                strOut += chr;
        }
    }

    return strOut;
}

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace
