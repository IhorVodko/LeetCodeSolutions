// problem : https://leetcode.com/problems/sparse-matrix-multiplication/description
// submission : https://leetcode.com/problems/sparse-matrix-multiplication/submissions/1621410364
// solution post : https://leetcode.com/problems/sparse-matrix-multiplication/solutions/6699814/
//    c-modern-readable-code-beats-100-runtime-h9tm

// #include <vector>
// #include <utility>

// let 'r1' be a rows count of the first matrix
// 'm' - columns count of the first matrix
// 'm' - rows count of the second matrix
// 'c2' - columns count of the second matrix
// time complexity O(r1 * m * c2)
// space complexity O(r1 * m + m * c2)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    template<typename T_>
    using Arr2T = std::vector<std::vector<T_>>;
    Arr2T<int> multiply(
        Arr2T<int> const & mx1_,
        Arr2T<int> const & mx2_
    ) const;
private:
    Arr2T<std::pair<int, size_t>> CompressMx(Arr2T<int> const & mx_) const;
};

Solution::Arr2T<int> Solution::multiply(
    Arr2T<int> const & mx1_,
    Arr2T<int> const & mx2_
) const {
    auto const rowsCount1{mx1_.size()};
    auto const colsCount1{mx1_.at(0).size()};
    auto const colsCount2{mx2_.at(0).size()};
    auto const mx1Comp{CompressMx(mx1_)};
    auto const mx2Comp{CompressMx(mx2_)};
    auto mxProduct{Arr2T<int>(rowsCount1, std::vector<int>(colsCount2, 0))};
    for(size_t r1{0}; r1 < rowsCount1; ++r1) {
        for(auto const [num1, c1]: mx1Comp.at(r1)) {
            for(auto const [num2, c2]: mx2Comp.at(c1)) {
                mxProduct[r1][c2] += num1 * num2;
            }
        }
    }
    return mxProduct;
}

Solution::Arr2T<std::pair<int, size_t>> Solution::CompressMx(
    Arr2T<int> const & mx_
) const {
    auto const rowsCount{mx_.size()};
    auto const colsCount{mx_.at(0).size()};
    auto compressedMx{Arr2T<std::pair<int, size_t>>(rowsCount)};
    for(size_t r{0}; r < rowsCount; ++r) {
        for(size_t c{0}; c < colsCount; ++c) {
            if(mx_[r][c] != 0) {
                compressedMx[r].emplace_back(mx_[r][c], c);
            }
        }
    }
    return compressedMx;
}
