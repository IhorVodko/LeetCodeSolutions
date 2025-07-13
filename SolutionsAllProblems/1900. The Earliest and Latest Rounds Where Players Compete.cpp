// problem : https://leetcode.com/problems/the-earliest-and-latest-rounds-where-players-compete/description/
// submission : https://leetcode.com/problems/the-earliest-and-latest-rounds-where-players-compete/submissions/
//    1696506398
// solution post : https://leetcode.com/problems/the-earliest-and-latest-rounds-where-players-compete/
//    solutions/6953992/c-modern-readable-code-beats-100-runtime-fhuo

// #include <algorithm>
// #include <array>
// #include <limits>
// #include <ranges>

namespace Util {
    inline auto constexpr kMaxPlayerCount{30};
}

class Solution {
public:
// let 'n' be a count of the given players
// time complexity O(n^4 * log2(n))
// space complexity O(n^3)
// runtime 0 ms, beats 100.00 %
    std::vector<int> earliestAndLatest(
        int const playerCount_,
        int firstPlayerPos_,
        int secondPlayerPos_
    );
private:
    using arr1T = std::array<int, Util::kMaxPlayerCount>;
    using arr2T = std::array<arr1T, Util::kMaxPlayerCount>;
    using arr3T = std::array<arr2T, Util::kMaxPlayerCount>;
    std::pair<int, int> DoDp(
        int const playerCount_,
        int const firstPlayerPos_,
        int const secondPlayerPos_
    );
    arr3T mPlayState1{};
    arr3T mPlayState2{};
};

std::vector<int> Solution::earliestAndLatest(
    int const playerCount_,
    int firstPlayerPos_,
    int secondPlayerPos_
) {
    if(firstPlayerPos_ > secondPlayerPos_) {
        std::swap(firstPlayerPos_, secondPlayerPos_);
    }
    auto const [minRound, maxRound]{
        DoDp(playerCount_, firstPlayerPos_, secondPlayerPos_)};
    return {minRound, maxRound};
}

std::pair<int, int> Solution::DoDp(
    int const playerCount_,
    int const firstPlayerPos_,
    int const secondPlayerPos_
) {
    using intT = std::numeric_limits<int>;
    namespace views = std::ranges::views;
    if(mPlayState1
        .at(playerCount_)
        .at(firstPlayerPos_)
        .at(secondPlayerPos_)
    ) {
        auto const minRound{mPlayState1
            .at(playerCount_)
            .at(firstPlayerPos_)
            .at(secondPlayerPos_)};
        auto const maxRound{mPlayState2.
            at(playerCount_).
            at(firstPlayerPos_).
            at(secondPlayerPos_)};
        return {minRound, maxRound};
    }
    if(firstPlayerPos_ + secondPlayerPos_ == playerCount_ + 1) {
        return {1, 1};
    } else if(firstPlayerPos_ + secondPlayerPos_ > playerCount_ + 1) {
        auto & minRoundNext{mPlayState1
            .at(playerCount_)
            .at(firstPlayerPos_)
            .at(secondPlayerPos_)};
        auto & maxRoundNext{mPlayState2
            .at(playerCount_)
            .at(firstPlayerPos_)
            .at(secondPlayerPos_)};
        auto const firstPlayerPosNext{playerCount_ + 1 - secondPlayerPos_};
        auto const secondPlayerPosNext{playerCount_ + 1 - firstPlayerPos_};
        std::tie(minRoundNext, maxRoundNext) =
            DoDp(playerCount_, firstPlayerPosNext, secondPlayerPosNext);
        auto const minRound{mPlayState1
            .at(playerCount_)
            .at(firstPlayerPos_)
            .at(secondPlayerPos_)};
        auto const maxRound{mPlayState2
            .at(playerCount_)
            .at(firstPlayerPos_)
            .at(secondPlayerPos_)};    
        return {minRound, maxRound};
    }
    auto minRound{intT::max()};
    auto maxRound{intT::min()};
    auto middlePos{(playerCount_ + 1) / 2};
    if(secondPlayerPos_ <= middlePos) {
        for(auto const pos1: views::iota(0, firstPlayerPos_)) {
            auto const posDistance{secondPlayerPos_ - firstPlayerPos_};
            for(auto const pos2: views::iota(0, posDistance)) {
                auto const firstPlayerPos{pos1 + 1};
                auto const secondPlayerPos{pos1 + pos2 + 2};
                auto const [minRoundCurr, maxRoundCurr]{
                    DoDp(middlePos, firstPlayerPos, secondPlayerPos)};
                minRound = std::min(minRound, minRoundCurr);
                maxRound = std::max(maxRound, maxRoundCurr);
            }
        }
    } else {
        auto const pos2Max{playerCount_ + 1 - secondPlayerPos_};
        auto const midPos{(playerCount_ - 2 * pos2Max + 1) / 2};
        for(auto const pos1: views::iota(0, firstPlayerPos_)) {
            auto const posDistance{pos2Max - firstPlayerPos_};
            for(auto const pos2: views::iota(0, posDistance)) {
                auto const firstPlayerPos{pos1 + 1};
                auto const secondPlayerPos{pos1 + pos2 + midPos + 2};
                auto const [minRoundCurr, maxRoundCurr]{
                    DoDp(middlePos, firstPlayerPos, secondPlayerPos)};
                minRound = std::min(minRound, minRoundCurr);
                maxRound = std::max(maxRound, maxRoundCurr);
            }
        }
    }
    auto & minRoundNext{mPlayState1
        .at(playerCount_)
        .at(firstPlayerPos_)
        .at(secondPlayerPos_)};
    minRoundNext = minRound + 1;
    auto & maxRoundNext{mPlayState2
        .at(playerCount_)
        .at(firstPlayerPos_)
        .at(secondPlayerPos_)};
    maxRoundNext = maxRound + 1;
    return {minRoundNext, maxRoundNext};
}
