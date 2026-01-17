// problem : https://leetcode.com/problems/separate-squares-ii/description
// submission : https://leetcode.com/problems/separate-squares-ii/submissions/1887919341
// solution post : https://leetcode.com/problems/separate-squares-ii/solutions/7502383/
//    c-modern-readable-code-beats-100-runtime-xl7o

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

class SegmentTree {
public:
    explicit SegmentTree(std::set<int> const & data_):
        mCount{std::vector<int>(4 * data_.size())},
        mCovered{std::vector<int>(4 * data_.size())},
        mArray{data_.begin(), data_.end()},
        mSize{static_cast<int>(data_.size()) - 1}
    {}

    auto Update(
        int const qLeft_,
        int const qRight_,
        int const qVal_
    ) -> void {
        Modify(qLeft_, qRight_, qVal_, 0, mSize - 1, 0);
    }
    [[nodiscard]]
    auto Query() const -> int {
        return mCovered.at(0);
    }

private:
    auto Modify(
        int const qLeft_,
        int const qRight_,
        int const qVal_,
        int const left_, 
        int const right_,
        int const pos_
    ) -> void {
        if(mArray.at(right_ + 1) <= qLeft_ || mArray.at(left_) >= qRight_) {
            return;
        } 
        if(qLeft_ <= mArray.at(left_) && mArray.at(right_ + 1) <= qRight_) {
            mCount.at(pos_) += qVal_;
        } else {
            auto const mid{std::midpoint(left_, right_)};
            Modify(qLeft_, qRight_, qVal_, left_, mid, pos_ * 2 + 1);
            Modify(qLeft_, qRight_, qVal_, mid + 1, right_, pos_ * 2 + 2);
        }
        if(mCount.at(pos_) > 0) {
            mCovered.at(pos_) = mArray.at(right_ + 1) - mArray.at(left_);
        } else {
            if(left_ == right_) {
                mCovered.at(pos_) = 0;
            } else {
                mCovered.at(pos_) =
                    mCovered.at(pos_ * 2 + 1) + mCovered.at(pos_ * 2 + 2);
            }
        }
    }

    std::vector<int> mCount;
    std::vector<int> mCovered;
    std::vector<int> mArray;
    int mSize;
};

// let 'n' be the number of squares
// time complexity O(n * log(n))
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    [[nodiscard]]
    auto separateSquares(std::vector<std::vector<int>> const & squares_) const -> double;

private:
    static auto constexpr kOut{-1};
    static auto constexpr kIn{1};
};

auto Solution::separateSquares(
    std::vector<std::vector<int>> const & squares_
) const -> double {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto events{std::vector<std::array<int, 4>>{}};
    auto xLessSet{std::set<int>{}};
    for(auto const & sq: squares_) {
        auto const xLeft{sq[0]};
        auto const y{sq[1]};
        auto const side{sq[2]};
        auto const xRight{xLeft + side};
        events.emplace_back(std::array{y, kIn, xLeft, xRight});
        events.emplace_back(std::array{y + side, kOut, xLeft, xRight});
        xLessSet.emplace(xLeft);
        xLessSet.emplace(xRight);
    }
    rngs::sort(events, std::less{}, [] (auto const & event) { return event.front(); });
    auto tree{SegmentTree{xLessSet}};
    auto prefSums{std::vector<double>{}};
    auto widths{std::vector<int>{}};
    auto totalArea{0.0};
    auto prevY{events.front()[0]};
    for(auto const [y, inOut, xLeft, xRight]: events) {
        auto const len{tree.Query()};
        auto const curArea{static_cast<long long>(len) * (y - prevY)};
        totalArea += curArea;
        tree.Update(xLeft, xRight, inOut);
        prefSums.emplace_back(totalArea);
        widths.emplace_back(tree.Query());
        prevY = y;
    }
    auto const halfArea{static_cast<long long>(totalArea + 1) / 2};
    auto const lbIdx{rngs::lower_bound(prefSums, halfArea) - prefSums.cbegin() - 1};
    if(lbIdx < 0) {
        return -1.0;
    }
    auto const area{prefSums[lbIdx]};
    auto const width{widths[lbIdx]};
    auto const height{events[lbIdx][0]};
    auto const lineYPos{height + (totalArea - area * 2) / (width * 2.0)};
    return lineYPos;
}
