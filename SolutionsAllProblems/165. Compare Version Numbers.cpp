// problem : https://leetcode.com/problems/compare-version-numbers/description/
// submission : https://leetcode.com/problems/compare-version-numbers/submissions/1781557104
// solution post : https://leetcode.com/problems/compare-version-numbers/solutions/7221010/
//    c-modern-readable-code-beats-100-runtime-pygs

// import std;

class Solution {
public:
// let 'l1' be a given first string length
// 'l2' - second string length 
// time complexity O(max(l1, l2))
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto compareVersion(
        std::string_view const v1_,
        std::string_view const v2_
    ) const -> int;

private:
    [[nodiscard]]
    auto TrimLeadingZeroes(std::string_view const sv_) const -> std::string_view;
    [[nodiscard]]
    auto Split(std::string_view const sv_) const;
    [[nodiscard]]
    auto CompareRevision(
        std::string_view const sv1_,
        std::string_view const sv2_
    ) const -> std::weak_ordering;

    inline static char constexpr kDelimmeter{'.'};
};

auto Solution::Split(std::string_view const sv_) const {
    namespace ranges = std::ranges;
    namespace views = std::views;

    auto const splittedRange{
        sv_ |
        views::split(kDelimmeter) |
        views::transform([] (auto && rng_) {
            auto const sv{
                std::string_view(rng_.data(), ranges::distance(rng_))};
            return sv;
        })
    };
    return splittedRange;
}

auto Solution::compareVersion(
    std::string_view const v1_,
    std::string_view const v2_
) const -> int {
    namespace ranges = std::ranges;
    namespace views = std::views;

    assert(!v1_.empty() && !v2_.empty());
    auto splittedV1{Split(v1_)};
    auto splittedV2{Split(v2_)};
    for(
        auto it1{splittedV1.cbegin()}, end1{splittedV1.cend()},
        it2{splittedV2.cbegin()}, end2{splittedV2.cend()};
        it1 != end1 || it2 != end2;
    ) {
        auto const rev1{(it1 != splittedV1.cend()) ? *it1++ : "0"sv};
        auto const rev2{(it2 != splittedV2.end()) ? *it2++ : "0"sv};
        auto const cmp{CompareRevision(rev1, rev2)};
        if(cmp < 0) {
            return -1;
        } else if(cmp > 0) {
            return 1;
        }
    }
    return 0;
}

auto Solution::TrimLeadingZeroes(
    std::string_view const sv_
) const -> std::string_view {
    auto const posNotZero{sv_.find_first_not_of('0')};
    if(posNotZero == std::string_view::npos) {
        auto const trimmedSv{"0"sv};
        return trimmedSv;
    }
    auto const trimmedSv{sv_.substr(posNotZero)};
    return trimmedSv;
}

auto Solution::CompareRevision(
    std::string_view const sv1_,
    std::string_view const sv2_
) const -> std::weak_ordering {
     using weak_ordering = std::weak_ordering;

    auto const trimmedSv1{TrimLeadingZeroes(sv1_)};
    auto const trimmedSv1Sz{trimmedSv1.size()};
    auto const trimmedSv2{TrimLeadingZeroes(sv2_)};
    auto const trimmedSv2Sz{trimmedSv2.size()};
    if(trimmedSv1Sz < trimmedSv2Sz) {
        return weak_ordering::less;
    } else if(trimmedSv1Sz > trimmedSv2Sz) {
        return weak_ordering::greater;
    } 
    auto cmp{trimmedSv1 <=> trimmedSv2};
    if(cmp < 0) {
        return weak_ordering::less;
    } else if(cmp > 0) {
        return weak_ordering::greater;
    }
    return weak_ordering::equivalent;
}
