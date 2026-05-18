// problem : https://leetcode.com/problems/jump-game-iii/description
// submission : https://leetcode.com/problems/jump-game-iii/submissions/2006717212
// solution post : https://leetcode.com/problems/jump-game-iii/solutions/8271471/c-modern-readable-code-beats-100-runtime-padx

// Approach : Breadth-First Search (BFS)
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the count of numbers
// complexity :  O(n)
// complexity : O(n)

// import std;

class Solution final {
public:
    [[nodiscard]]
    auto canReach(
        std::vector<int> const & nums_,
        int const startIdx_
    ) const -> bool;

private:
    static auto constexpr kTargetNum{0};
};

auto Solution::canReach(
    std::vector<int> const & nums_,
    int const startIdx_
) const -> bool {
    namespace vs = std::views;

    auto const numsSz{std::ssize(nums_)};
    if(numsSz == 1) {
        return true;
    }
    
    // Prevent cycles
    auto isVisited{std::vector<bool>(numsSz)};
    isVisited.front() = false;
    // BFS queue
    auto qIdxs{std::queue<int>{}};
    qIdxs.emplace(startIdx_);

    // Helper to process next BFS nodes
    auto const ProcessNextIdx{[&] (auto const idx_) {
        if(0 <= idx_ && idx_ <= numsSz  && !isVisited[idx_]) {
            qIdxs.emplace(idx_);
            isVisited[idx_] = true;
        }  
    }};

    // Do BFS
    while(!qIdxs.empty()) {
        auto const idx{qIdxs.front()};
        qIdxs.pop();
    
        auto const num{nums_[idx]};
        if(num == kTargetNum) {
            return true;
        }
        // Jump backwards
        ProcessNextIdx(idx - num);
        // Jump forwards
        ProcessNextIdx(idx + num);
    }

    // Target nubmer is not reachable
    return false;
}

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
