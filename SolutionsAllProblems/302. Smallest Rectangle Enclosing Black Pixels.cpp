// problem : https://leetcode.com/problems/smallest-rectangle-enclosing-black-pixels/description/
// submission : https://leetcode.com/problems/smallest-rectangle-enclosing-black-pixels/submissions/1616976476
// solution post : https://leetcode.com/problems/smallest-rectangle-enclosing-black-pixels/solutions/6684571/
//     c-modern-readable-code-beats-100-runtime-6tq1

// #include <algorithm>
// #include <queue>
// #include <vector>

namespace Utility{
    auto constexpr kWhitePixel{'0'};
    auto constexpr kBlackPixel{'1'};
    auto constexpr kVisitedPixel{'2'};
    auto constexpr kMoves{std::array<std::pair<int, int>, 4>{{
        {-1, 0}, {0, -1}, {1, 0}, {0, 1}
    }}};
}

// let 'l' be a length of the given image
// 'w' - width of the given image
// time complexity O(l * w)
// space complexity O(l * w)
// runtime 0 ms, beats 100.00 %
class Solution {
public:
    using Arr2T = std::vector<std::vector<char>>;
    using PixelT = std::pair<int, int>;
    int minArea(Arr2T & image_,
        int const r_,
        int const c_
    ) const;
private:
    bool IsPixelWithinImage(
        Arr2T const & image_,
        PixelT const & pixel_
    ) const;
};

int Solution::minArea(Arr2T & image_,
    int const r_,
    int const c_
) const {
    using namespace Utility;
    auto pixelsQ{std::queue<PixelT>{{{r_, c_}}}};
    image_.at(r_).at(c_) = kVisitedPixel;
    auto rMin{r_};
    auto rMax{r_};
    auto cMin{c_};
    auto cMax{c_};
    while(!pixelsQ.empty()) {
        auto [rCurr, cCurr]{pixelsQ.front()}; 
        pixelsQ.pop();
        for(auto const [rMove, cMove]: kMoves) {
            auto const rNext{rCurr + rMove};
            auto const cNext{cCurr + cMove};
            if(!(IsPixelWithinImage(image_, {rNext, cNext}) &&
                image_[rNext][cNext] == kBlackPixel
            )) {
                continue;
            }
            pixelsQ.emplace(rNext, cNext);
            image_[rNext][cNext] = kVisitedPixel;
            rMin = std::min(rMin, rNext);
            rMax = std::max(rMax, rNext);
            cMin = std::min(cMin, cNext);
            cMax = std::max(cMax, cNext);
        }
    }
    auto const rectangleArea{(rMax - rMin + 1) * (cMax - cMin + 1)};
    return rectangleArea;
}

bool Solution::IsPixelWithinImage(
    Arr2T const & image_,
    PixelT const & pixel_
) const {
    auto const [r, c]{pixel_};
    auto const rowsCount{image_.size()};
    auto const colsCount{image_.at(0).size()};
    return 0 <= r && r < rowsCount && 0 <= c && c < colsCount;
}
