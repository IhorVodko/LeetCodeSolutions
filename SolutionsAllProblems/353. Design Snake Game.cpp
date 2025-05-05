// problem : https://leetcode.com/problems/design-snake-game/description/
// submission : https://leetcode.com/problems/design-snake-game/submissions/1626222274
// solution post : https://leetcode.com/problems/design-snake-game/solutions/6717433/
//     c-modern-readable-code-by-cyberartist-ipx8

// #include <queue>
// #include <string>
// #include <vector>
// #include <unordered_map>

namespace Utility {
    auto const kDirectionToOffset{
        std::unordered_map<char, std::pair<int, int>>{
            {'U', {-1, 0}}, {'D', {1, 0}}, {'L', {0, -1}}, {'R', {0, 1}}}};
    auto constexpr kEmpty{0};
    auto constexpr kSnake{1};
    auto constexpr kFood{2};
}

// let 'w' be a given width
// 'h' - heights
// time complexity O(w * h)
// space complexity O(w * h)
// runtime 108 ms, beats 33.49 %
class SnakeGame {
public:
    using Arr2T = std::vector<std::vector<int>>;
// time complexity O(w * h)
// space complexity O(w * h)
    SnakeGame(
        int const width_,
        int const height_,
        Arr2T & food_
    );
// time complexity O(1)
// space complexity O(w * h)
    int move(std::string const & direction_);
private:
    using PixelT = std::pair<int, int>;
    bool IsPixelOnScreen(PixelT const pixel_) const;
    void UpdateTail();
    void SetFoodOnScreen(size_t const score_);
    int GetWidth() const;
    int GetHeight() const;
    size_t mScore;
    int mWidth;
    int mHeight;
    PixelT mTail;
    PixelT mHead;
    Arr2T mScreen;
    Arr2T mFood;
    std::queue<char> mMoves;
};

SnakeGame::SnakeGame(
    int const width_,
    int const height_,
    Arr2T & food_
):
    mScore{0},
    mWidth(width_),
    mHeight(height_),
    mTail{0, 0},
    mHead{0, 0},
    mScreen(height_, std::vector<int>(width_, Utility::kEmpty)),
    mFood{std::move(food_)}
{
    SetFoodOnScreen(mScore);
}
int SnakeGame::move(std::string const & direction_) {
    using namespace Utility;
    mMoves.emplace(direction_[0]);
    auto const & [rOffset, cOffcet]{kDirectionToOffset.at(direction_[0])};
    auto rNext{mHead.first + rOffset};
    auto cNext{mHead.second + cOffcet};
    if(!IsPixelOnScreen({rNext, cNext})) {
        return -1;
    }
    auto & pixelValNext{mScreen[rNext][cNext]};
    if(pixelValNext == kFood) {
        if(++mScore < mFood.size()) {
            SetFoodOnScreen(mScore);
        }
    } else {
        UpdateTail();
        if(pixelValNext == kSnake) {
            return -1;
        }
    }
    pixelValNext = kSnake;
    mHead = {rNext, cNext};
    return mScore; 
}
bool SnakeGame::IsPixelOnScreen(PixelT const pixel_) const {
    auto const r{pixel_.first};
    auto const c{pixel_.second}; 
    return 0 <= r && r < GetHeight() && 0 <= c && c < GetWidth();
}
void SnakeGame::UpdateTail() {
    using namespace Utility;
    auto const move{mMoves.front()};
    mMoves.pop();
    auto & [r, c]{mTail};
    mScreen.at(r).at(c) = kEmpty;
    auto const [rOffset, cOffset]{kDirectionToOffset.at(move)};
    r += rOffset;
    c += cOffset;
}
void SnakeGame::SetFoodOnScreen(size_t const score_) {
    using namespace Utility;
    auto const & food{mFood.at(score_)};
    mScreen.at(food.at(0)).at(food.at(1)) = kFood;
}
int SnakeGame::GetWidth() const {
    return mWidth;
}
int SnakeGame::GetHeight() const {
    return mHeight;
}

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame* obj = new SnakeGame(width, height, food);
 * int param_1 = obj->move(direction);
 */
