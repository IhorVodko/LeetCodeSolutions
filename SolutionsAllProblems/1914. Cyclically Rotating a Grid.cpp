// problem : https://leetcode.com/problems/cyclically-rotating-a-grid/description
// submission : https://leetcode.com/problems/cyclically-rotating-a-grid/submissions/1998859435
// solution post : https://leetcode.com/problems/cyclically-rotating-a-grid/solutions/8178698/c-modern-readable-code-by-cyberartist-ix6k

// Approach : Layer-by-Layer Extraction with Cyclic Reinsertion
// Runtime : 7 ms, beats 97.79 %

// Complexity
// let 'n' by 'm' be the given grid size
// 'maxN' by 'maxM' - maximum possible grid size
// complexity :  O(n * m)
// complexity : O(maxN + maxM) = O(1) 

// import std;

namespace {

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

class Solution final {
public:
    using arr2dT = std::vector<std::vector<int>>;
    
    static auto rotateGrid(
        arr2dT & grid_,
        int const rotSteps_
    ) -> arr2dT;

private:
    static inline auto IncCyclic(
        int & idx,
        int const perimeter_
    ) noexcept -> void;

    // Max perimeter for a 50x50 grid is 196 elements
    static auto constexpr kMaxLayerSz{196};
};

auto Solution::rotateGrid(
    arr2dT & grid_,
    int const rotSteps_
) -> arr2dT {
    namespace vs = std::views;

    auto const rSz{std::ssize(grid_)};
    auto const cSz{std::ssize(grid_.front())};
    auto layer{std::array<int, kMaxLayerSz>{}};
    // Total number of concentric layers
    auto const layesrSz{std::min(rSz, cSz) / 2};
    
    // Process each layer from outermost to innermost
    for(auto const layerIdx: vs::iota(0, layesrSz)) {
        // Start row index for the current layer
        auto const currRFirst{layerIdx};
        // End row index for the current layer
        auto const currRLast{rSz - layerIdx - 1};
        // Start column index for the current layer
        auto const currCFirst{layerIdx};
        // End column index for the current layer
        auto const currCLast{cSz - layerIdx - 1};

        auto const currRSz{rSz - 2 * layerIdx};
        auto const currCSz{cSz - 2 * layerIdx};
        auto const perimeter{(currRSz + currCSz - 2) * 2};
        auto idx{0};

        // Extract the top edge elements
        for(auto j: vs::iota(0, currCSz - 1)) {
            layer[idx++] = grid_[currRFirst][currCFirst + j];
        }

        // Extract the right edge elements
        for(auto const j: vs::iota(0, currRSz - 1)) {
            layer[idx++] = grid_[currRFirst + j][currCLast];
        }

        // Extract the bottom edge elements
        for(auto const j: vs::iota(0, currCSz - 1)) {
            layer[idx++] = grid_[currRLast][currCLast - j];
        }

        // Extract the left edge elements
        for(auto const j: vs::iota(0, currRSz - 1)) {
            layer[idx++] = grid_[currRLast - j][currCFirst];
        } 

        // Find the start index in the buffer after rotSteps_ shifts
        idx = rotSteps_ % perimeter;

        // Place the top edge elements back into the grid
        for(auto const j: vs::iota(0, currCSz - 1)) {
            grid_[currRFirst][currCFirst + j] = layer[idx];
            IncCyclic(idx, perimeter);
        }

        // Place the right edge elements back into the grid
        for(auto const j: vs::iota(0, currRSz - 1)) {
            grid_[currRFirst + j][currCLast] = layer[idx];
            IncCyclic(idx, perimeter);
        } 

        // Place the bottom edge elements back into the grid
        for(auto const j: vs::iota(0, currCSz - 1)) {
            grid_[currRLast][currCLast - j] = layer[idx];
            IncCyclic(idx, perimeter);
        }

        // Place the left edge elements back into the grid
        for(auto const j: vs::iota(0, currRSz - 1)) {
            grid_[currRLast - j][currCFirst] = layer[idx];
            IncCyclic(idx, perimeter);
        }
    }

    // Return the cyclically rotated grid
    return grid_;
}

inline auto Solution::IncCyclic(
    int & idx_,
    int const perimeter_
) noexcept -> void {
    idx_ = (idx_ == perimeter_ - 1) ? 0 : (idx_ + 1);
}
