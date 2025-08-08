// problem : https://leetcode.com/problems/find-the-maximum-number-of-fruits-collected/description/
// submission : https://leetcode.com/problems/find-the-maximum-number-of-fruits-collected/submissions/1728062991
// solution post : https://leetcode.com/problems/find-the-maximum-number-of-fruits-collected/solutions/7058256
//    /c-modern-readable-code-optimal-time-comp-95fs

// #include <algorithm>
// #include <limits>
// #include <ranges>
// #include <vector>

class Solution {
public:
    using fruitT = int;
    using fruitsT = std::vector<fruitT>;
    using mxFruitT = std::vector<fruitsT>;
// let 'n' by 'n' be a size of the given matrix
// time complexity O(n^2)
// space complexity O(n)
// runtime 47 ms, beats 82.72 %
    int maxCollectedFruits(mxFruitT & mxFruits_);
private:
    [[nodiscard]]
    int CollectMaxFruitsPlayer1() const;
    [[nodiscard]]
    int CollectMaxFruitsPlayer2() const;
    int CollectMaxFruitsPlayer3();
    [[nodiscard]]
    int collectMaxFruits() const;
    void TransposeMx();
    std::optional<std::reference_wrapper<mxFruitT>> mMxFruits;
};

int Solution::maxCollectedFruits(mxFruitT & mxFruits_) {
    mMxFruits = mxFruits_;
    auto & mxFruits = mMxFruits.value().get();
    auto const colRowSz{static_cast<int>(mxFruits.size())};
    auto maxFruitsCollected{CollectMaxFruitsPlayer1()};
    maxFruitsCollected += CollectMaxFruitsPlayer2();
    maxFruitsCollected += CollectMaxFruitsPlayer3();
    return maxFruitsCollected;
}

int Solution::CollectMaxFruitsPlayer1() const {
    namespace views = std::views;
    auto & mxFruits = mMxFruits.value().get();
    auto maxFruitsCollected{0};
    auto const colRowSz{static_cast<int>(mxFruits.size())};
    for(auto const idx: views::iota(0, colRowSz)) {
        maxFruitsCollected += mxFruits.at(idx).at(idx);
    }
    return maxFruitsCollected;
}

int Solution::CollectMaxFruitsPlayer2() const {
    auto const maxFruitsCollected{collectMaxFruits()};
    return maxFruitsCollected;
}

int Solution::CollectMaxFruitsPlayer3() {
    TransposeMx();
    auto const maxFruitsCollected{collectMaxFruits()};
    return maxFruitsCollected;
}

int Solution::collectMaxFruits() const {
    namespace views = std::views;
    using intT = std::numeric_limits<int>;
    auto & mxFruits = mMxFruits.value().get();
    auto const colRowSz{static_cast<int>(mxFruits.size())};
    auto prevDp{std::vector<fruitT>(colRowSz, intT::min())};
    auto currDp{std::vector<fruitT>(colRowSz, intT::min())};
    prevDp.at(colRowSz - 1) = mxFruits.at(0).at(colRowSz - 1);
    for(auto const idx: views::iota(1, colRowSz - 1)) {
        for(auto const j: views::iota(
            std::max(colRowSz - 1 - idx, idx + 1),
            colRowSz
        )) {
            auto maxFruits{prevDp.at(j)};
            if(j - 1 >= 0) {
                maxFruits = std::max(maxFruits, prevDp.at(j - 1));
            } 
            if(j + 1 < colRowSz) {
                maxFruits = std::max(maxFruits, prevDp.at(j + 1));
            }
            currDp.at(j) = maxFruits + mxFruits.at(idx).at(j);
        }
        std::swap(prevDp, currDp);
    }
    auto const maxFruits{prevDp.at(colRowSz - 1)};
    return maxFruits;
}

void Solution::TransposeMx() {
    namespace views = std::views;
    auto & mxFruits = mMxFruits.value().get();
    auto const colRowSz{static_cast<int>(mxFruits.size())};
    for(auto const idx: views::iota(0, colRowSz)) {
        for(auto const j: views::iota(0, idx)) {
            std::swap(mxFruits.at(j).at(idx), mxFruits.at(idx).at(j));
        }
    }
}
