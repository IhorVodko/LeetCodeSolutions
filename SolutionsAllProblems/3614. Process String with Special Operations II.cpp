// problem : https://leetcode.com/problems/process-string-with-special-operations-ii/description
// submission : https://leetcode.com/problems/process-string-with-special-operations-ii/submissions/2036537941
// solution post : https://leetcode.com/problems/process-string-with-special-operations-ii/solutions/8340346/
//    c-modern-readable-code-optimal-time-comp-o9ea

// Approach :
// Runtime : 10 ms, beats 99.85 %


// Complexity
// let 'n' be the given string length
// Time :  O(n)
// Space : O(1)

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto processStr(
        std::string_view const str_,
        long long targetIdx_
    ) noexcept -> char;

private:
    static auto constexpr kRemoveLast{'*'};
    static auto constexpr kDuplicate{'#'};
    static auto constexpr kReverse{'%'};
    static auto constexpr kDefaultVal{'.'};
    static auto constexpr kError{'?'};
};

auto Solution::processStr(
    std::string_view const str_,
    long long targetIdx_
) noexcept -> char {
    namespace vs = std::views;

    // assert(1 <= str_.length() && str_.length() <= 100'000);
    // assert(0 <= targetIdx_ && targetIdx_ <= 1'000'000'000'000'000);

    auto len{0ll};

    // Calculate final sequence length
    for(auto const chr: str_) {
        switch(chr) {
            case kRemoveLast:
                if(len > 0) {
                    --len;
                }
                break;
            case kDuplicate:
                len *= 2;
                break;
            case kReverse:
                break;
            default:
                // assert(std::islower(chr));

                ++len;
        }
    }

    // Catch out-of-bounds index
    if(targetIdx_ >= len) {
        return kDefaultVal;
    }

    // Reverse map target index to original character
    for(auto const chr: str_ | vs::reverse) {
        switch(chr) {
            case kRemoveLast:
                ++len;
                break;
            case kDuplicate:
                len /= 2;

                //assert(len != 0);

                // Fold index into pre-duplicated segment
                targetIdx_ %= len;
                break;
            case kReverse:
                // Mirror index relative to current bounds
                targetIdx_ = len - 1 - targetIdx_;
                break;
            default:
                // assert(std::islower(chr));

                if(targetIdx_ == len - 1) {
                    return chr;
                }
                --len;
        }
    }

    // Should never be executed
    return kError;
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
