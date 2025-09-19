// problem : https://leetcode.com/problems/design-spreadsheet/description/
// submission : https://leetcode.com/problems/design-spreadsheet/submissions/1776172913
// solution post : https://leetcode.com/problems/design-spreadsheet/solutions/7205850/
//     c-modern-readable-code-optimal-time-comp-sj2q

// import std;

/**
 * Your Spreadsheet object will be instantiated and called as such:
 * Spreadsheet* obj = new Spreadsheet(rows);
 * obj->setCell(cell,value);
 * obj->resetCell(cell);
 * int param_3 = obj->getValue(formula);
 */

// let 'r' be a number of rows given
// 'c' - number of culumns given
// runtime 58 ms, beats 86.44 %
class Spreadsheet {
public:
// time complexity O(c * r)
// space complexity O(c * r)
    Spreadsheet(int const rowCnt_);
// time complexity O(1)
// space complexity O(1)
    auto setCell(
        std::string const & cell_,
        int const val_
    ) -> void;
// time complexity O(1)
// space complexity O(1)
    auto resetCell(std::string const & cell_) -> void;
// time complexity O(1)
// space complexity O(1)
    [[nodiscard]]
    auto getValue(std::string const & formula_) const -> int;

private:
    using rowT = std::array<int, 26>;

    auto GetRowColIdxs(
        std::string const & cell_
    ) const -> std::pair<int, char>;
    [[nodiscard]]
    auto GetValue(std::string const & cell_) const -> int;

    static inline bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
    static inline int constexpr kRowIdxOffset{1};
    static inline char constexpr kColIdxOffset{'A'};
    std::vector<rowT> mGrid;
};

Spreadsheet::Spreadsheet(int const rowCnt_):
    mGrid(rowCnt_, rowT{})
{}

auto Spreadsheet::setCell(
    std::string const & cell_,
    int const val_
) -> void {
    auto const [rowIdx, colIdx]{GetRowColIdxs(cell_)};
    mGrid.at(rowIdx).at(colIdx) = val_;
}

auto Spreadsheet::resetCell(std::string const & cell_) -> void {
    auto const [rowIdx, colIdx]{GetRowColIdxs(cell_)};
    mGrid.at(rowIdx).at(colIdx) = 0;
}

auto Spreadsheet::getValue(std::string const & formula_) const -> int {
    namespace view = std::views;
    namespace ranges = std::ranges;
    auto rng{formula_ | views::drop(1) | views::split('+')};
    auto subRng{*rng.cbegin()};
    auto cell{std::string{subRng.cbegin(), subRng.cend()}};
    auto val1{GetValue(cell)};
    subRng = *ranges::next(rng.cbegin(), 1);
    cell = {subRng.cbegin(), subRng.cend()};
    auto val2{GetValue(cell)};
    auto const valRes{val1 + val2};
    return valRes;
}

auto Spreadsheet::GetRowColIdxs(
    std::string const & cell_
) const -> std::pair<int, char> {
    auto const rowIdx{std::stoi({cell_, 1}) - kRowIdxOffset};
    auto const colIdx{cell_.at(0) - kColIdxOffset};
    return {rowIdx, colIdx};
}

auto Spreadsheet::GetValue(std::string const & cell_) const -> int {
    auto val{-1};
    if(std::isalpha(cell_.at(0))) {
        auto const [rowIdx, colIdx]{GetRowColIdxs(cell_)};
        val = mGrid.at(rowIdx).at(colIdx);
    } else {
        val = std::stoi(cell_);
    }
    return val;
}
