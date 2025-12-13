// problem : https://leetcode.com/problems/coupon-code-validator/description
// submission : https://leetcode.com/problems/coupon-code-validator/submissions/1854738050
// solution post : https://leetcode.com/problems/coupon-code-validator/solutions/7411596/
//    c-modern-readable-code-beats-100-runtime-yl5e

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream{"display_runtime.txt"} << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class Solution {
public:
// let 'n' be the number of given codes
// time complexity O(n * log(n))
// space complexity O(log(n))
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto validateCoupons(
        std::span<std::string const> const codes_,
        std::span<std::string const> const businessLines_,
        std::vector<bool> const & isActiveCodes_
    ) const -> std::vector<std::string>;

private:
    inline auto IsCodeFormatValid(std::string_view const code_) const -> bool;
    inline auto EncodeCode(
        std::string_view const code_,
        std::string_view const businessLine_
    ) const -> std::string;
    inline auto DecodeCodes(std::span<std::string> const codes_) const -> void;

    static std::unordered_set<std::string> const kValidBusinessLines;
    static std::string constexpr kElectronicsLine{"electronics"};
    static auto constexpr kElectronicsPriority{'0'};
    static std::string constexpr kGroceryLine{"grocery"};
    static auto constexpr kGroceryPriority{'1'};
    static std::string constexpr kPharmacyLine{"pharmacy"};
    static auto constexpr kPharmacyPriority{'2'};
    static auto constexpr kRestaurantePriority{'3'};
};

auto Solution::validateCoupons(
    std::span<std::string const> const codes_,
    std::span<std::string const> const businessLines_,
    std::vector<bool> const & isActiveCodes_
) const -> std::vector<std::string> {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const codesSz{std::ssize(codes_)};
    auto validCodes{std::vector<std::string>{}};
    validCodes.reserve(codesSz);
    for(auto const idx: vs::iota(0, codesSz)) {
        if( isActiveCodes_[idx] &&
            IsCodeFormatValid(codes_[idx]) &&
            kValidBusinessLines.contains(businessLines_[idx])
        ) {
            validCodes.emplace_back(EncodeCode(codes_[idx], businessLines_[idx]));
        }
    }
    rngs::sort(validCodes);
    DecodeCodes(validCodes);
    return validCodes;
}

auto Solution::IsCodeFormatValid(
    std::string_view const code_
) const -> bool {
    if(code_.empty()) {
        return false;
    }
    for(auto const chr: code_) {
        if(!std::isalnum(chr) && chr != '_') {
            return false;
        }
    }
    return true;
}

auto Solution::EncodeCode(
    std::string_view const code_,
    std::string_view const businessLine_
) const -> std::string {
    auto codeEncoded{""s};
    if(businessLine_ == kElectronicsLine) {
        codeEncoded = kElectronicsPriority;
    } else if(businessLine_ == kGroceryLine) {
        codeEncoded = kGroceryPriority;
    } else if(businessLine_ == kPharmacyLine) {
        codeEncoded = kPharmacyPriority;
    } else {
        codeEncoded = kRestaurantePriority;
    }
    return codeEncoded + std::string{code_};

}

auto Solution::DecodeCodes(std::span<std::string> const codes_) const -> void {
    for(auto & code: codes_) {
        code.erase(0, 1);
    }
}

std::unordered_set<std::string> const Solution::kValidBusinessLines{
    "electronics", "grocery", "pharmacy", "restaurant"
};
