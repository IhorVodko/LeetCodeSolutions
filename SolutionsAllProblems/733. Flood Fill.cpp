// problem : https://leetcode.com/problems/flood-fill/description/
// submission : https://leetcode.com/problems/flood-fill/submissions/1554137055
// solution post : https://leetcode.com/problems/flood-fill/solutions/6463665/
//     c-modern-readable-code-beats-100-runtime-zewc

// #include <array>
// #include <queue>
// #include <vector>

// runtime 0 ms, beats 100.00 %
namespace Constants {
    auto constexpr moves{std::array<std::pair<int, int>, 4>{{
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}}}};
}

// let 'n' be a number of pixels in the image
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using PixelT = std::pair<int, int>;
    using ImageT = std::vector<std::vector<int>>;
    ImageT floodFill(
        ImageT & image,
        int const rowStart,
        int const colStart,
        int const color
    ) const {
        using namespace Constants;
        if(image.at(rowStart).at(colStart) == color) {
            return image;
        }
        auto const oldColor{image.at(rowStart).at(colStart)};
        auto pixels{std::queue<PixelT>{{{rowStart, colStart}}}};
        image.at(rowStart).at(colStart) = color;
        while(!pixels.empty()) {
            auto const [rowCurr, colCurr]{pixels.front()};
            pixels.pop();
            for(auto const & move: moves) {
                auto const rowNext{rowCurr + move.first};
                auto const colNext{colCurr + move.second};
                if(IsCellWithinBorders({rowNext, colNext}, image) &&
                    image.at(rowNext).at(colNext) == oldColor
                ) {
                    image.at(rowNext).at(colNext) = color;
                    pixels.emplace(rowNext, colNext);
                } 
            }
        }
        return image;
    }
private:
    bool IsCellWithinBorders(
        PixelT const & pixel,
        ImageT const & image
    ) const {
        auto const [row, col]{pixel};
        auto const rowsCount{image.size()};
        auto const colsCount{image.at(0).size()};
        return 0 <= row && row < rowsCount && 0 <= col && col < colsCount; 
    }
};
