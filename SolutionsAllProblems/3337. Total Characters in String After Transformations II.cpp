// problem : https://leetcode.com/problems/total-characters-in-string-after-transformations-ii/description/
// submission : https://leetcode.com/problems/total-characters-in-string-after-transformations-ii/submissions/
//    1634011197
// solution post : https://leetcode.com/problems/total-characters-in-string-after-transformations-ii/solutions/
//    6744640/c-modern-readable-code-optimal-time-comp-0nzi

// #include <array>
// #include <vector>

namespace Utility {
    auto constexpr kMod{static_cast<int>(1e9) + 7};
    auto constexpr kAlphabetSize{26};
    auto constexpr kAlphabetBegin{'a'};

struct Mx {
    explicit Mx(bool isIdentityMx_ = false);
    std::array<std::array<int, kAlphabetSize>, kAlphabetSize> mMx;
};

Mx::Mx(bool isIdentityMx_) {
    auto const val{isIdentityMx_ ? 1 : 0};
    auto i{0};
    for(auto & row : mMx) {
        row.fill(0);
        row.at(i) = val;
        ++i;
    }
}

Mx operator*(
    Mx const & multiplicand_,
    Mx const & multiplier_
) {
    Mx product;
    for (auto i1{0}; i1 < kAlphabetSize; ++i1) {
        for (int i2{0}; i2 < kAlphabetSize; ++i2) {
            for (int i3{0}; i3 < kAlphabetSize; ++i3) {
                product.mMx[i1][i2] = (product.mMx[i1][i2] +
                static_cast<long long>(multiplicand_.mMx[i1][i3]) *
                multiplier_.mMx[i3][i2]) % kMod;
            }
        }
    }
    return product;
}

Mx & operator*=(
    Mx & multiplicand_,
    Mx & multiplier_
) {
    multiplicand_ = multiplicand_ * multiplier_;
    return multiplicand_;
}

Mx doExpMul(
    Mx const & base_,
    int exp_
) {
    auto result{Mx(true)};
    auto base{base_};
    while (exp_) {
        if (exp_ % 2 == 1) {
            result *= base;
        }
        base *= base;
        exp_ /= 2;
    }
    return result;
}

}

class Solution {
public:
// let 's' be a length of the given string
// 't' - count of transformations given
// 'c' - count of elements of the charset given (26 in our case)
// time complexity O(s + log2(t) * c^3)
// space complexity O(c^2)
// runtime 204 ms, beats 87.50 %
    int lengthAfterTransformations(
        std::string const & str_,
        int const transCountTotal_,
        std::vector<int> const & newChrsCounts_
    ) const;
};

int Solution::lengthAfterTransformations(
    std::string const & str_,
    int const transCountTotal_,
    std::vector<int> const & newChrsCounts_
) const {
    using namespace Utility;
    auto chrsCountsMx{Mx{}};
    for(auto i1{0}; i1 < kAlphabetSize; ++i1) {
        for(auto i2{1}; i2 <= newChrsCounts_.at(i1); ++i2) {
            chrsCountsMx.mMx.at((i1 + i2) % kAlphabetSize).at(i1) = 1;
        }
    }
    auto chrsCountsMxFinal{doExpMul(chrsCountsMx, transCountTotal_)};
    auto strLengthAfterTrans{0};
    auto chrsCounts(std::vector<int>(kAlphabetSize, 0));
    for(auto const chr: str_) {
        ++chrsCounts.at(chr - kAlphabetBegin);
    }
    for(auto i{0}; i < kAlphabetSize; ++i) {
        for(auto j{0}; j < kAlphabetSize; ++j) {
            strLengthAfterTrans = (strLengthAfterTrans +
                static_cast<long long>(chrsCountsMxFinal.mMx[i][j]) *
                chrsCounts[j]) % kMod;
        }
    }
    return strLengthAfterTrans;
}
