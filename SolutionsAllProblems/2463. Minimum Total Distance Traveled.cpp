// problem : https://leetcode.com/problems/minimum-total-distance-traveled/description
// submission : https://leetcode.com/problems/minimum-total-distance-traveled/submissions/1978378646
// solution post : https://leetcode.com/problems/minimum-total-distance-traveled/solutions/7910101/
//    c-modern-readable-code-beats-100-runtime-1u0t

// Approach : Dynamic Programming with Monotonic Queue Optimization
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the number of robots
// 'm' - number of factories
// complexity :  O(n * log(n) + m * log(m) + n * m)
// complexity : O(n)

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
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
    using ll = long long;

    [[nodiscard]]
    auto minimumTotalDistance(
        std::vector<int> posPerRobot_,
        std::vector<std::vector<int>> posAndCapPerFactory_
    ) const -> ll;

private:
    static auto constexpr kLlInf{std::numeric_limits<ll>::max() / 2};
    // Max number of robots is 100, so 101 handles 1-based DP indexing securely.
    static auto constexpr kMaxCnt{101uz};
};

auto Solution::minimumTotalDistance(
    std::vector<int> posPerRobot_,
    std::vector<std::vector<int>> posAndCapPerFactory_
) const -> ll {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const robotTotCnt{std::ssize(posPerRobot_)};

    // Sort robots and factories by position to allow optimal sequential assignment
    // left-to-right
    rngs::sort(posPerRobot_);
    rngs::sort(posAndCapPerFactory_, std::less{},
        [](auto const & posAndCap_){ return posAndCap_[0]; });

    // currMinDistDp[j] stores the min distance to repair 'j' robots using factories
    // processed so far
    std::array<ll, kMaxCnt> currMinDistDp{};
    
    // Base case: 0 robots take 0 distance. >0 robots take infinity initially.
    rngs::fill(currMinDistDp | vs::drop(1), kLlInf);

    // Prefix sum of distances from the currently processed factory to the first 'j'
    // robots
    std::array<ll, kMaxCnt> prefDistPerRobot{};
    // nextMinDistDp[j] stores the min distance to repair 'j' robots considering the
    // current factory
    std::array<ll, kMaxCnt> nextMinDistDp{};
    // Monotonic queue implemented as a fixed-size array to store {dp_value, robot_index}
    std::array<std::pair<ll, int>, kMaxCnt> qDpMinDistAndRobot{};

    for(auto const & factoryPosAndCap: posAndCapPerFactory_) {
        // Skip factories that can't repair any robots to save time
        if(factoryPosAndCap[1] == 0) {
            continue;
        }

        auto const factoryPos{static_cast<ll>(factoryPosAndCap[0])};
        auto const factoryCap{factoryPosAndCap[1]};

        // Precompute the cumulative (prefix) sum of distances from the current factory 
        // to each robot. This allows O(1) distance calculation for a range of robots.
        for(auto const j: vs::iota(0, robotTotCnt)) {
            auto const dist{std::abs(static_cast<ll>(posPerRobot_[j]) - factoryPos)};
            prefDistPerRobot[j + 1] = prefDistPerRobot[j] + dist;
        }

        // Initialize head and tail for our array-based monotonic queue
        auto head{0};
        auto tail{0};

        // Seed the queue with the state representing 0 robots assigned to the current
        // factory
        qDpMinDistAndRobot[tail++] = {currMinDistDp[0], 0};

        for(auto const j: vs::iota(1, robotTotCnt + 1)) {
            // 1. Maintain Window Size (Capacity Limit)
            // If the oldest element in the queue exceeds the factory's capacity limit,
            // pop it. (j - factoryCap) is the minimum index of a robot we can start
            // repairing from.
            if(head < tail && qDpMinDistAndRobot[head].second < j - factoryCap) {
                ++head;
            }

            // 2. Default State Transition
            // What if we don't assign the j-th robot to this factory at all? We just
            // carry over the best cost from the previous factories.
            nextMinDistDp[j] = currMinDistDp[j];

            // 3. Optimal State Transition using Monotonic Queue
            // If the queue has valid previous states, calculate the cost if we assign 
            // robots from the optimal previous state (qDpMinDistAndRobot[head].first)
            // to the current factory.
            if(head < tail) {
                auto const currDist{
                    qDpMinDistAndRobot[head].first + prefDistPerRobot[j]};

                // Update nextMinDistDp if assigning them to this factory is strictly better
                if(currDist < nextMinDistDp[j]) {
                    nextMinDistDp[j] = currDist;
                }
            }

            // 4. Prepare Queue for the next robot (j+1)
            // Only add reachable states to the monotonic queue.
            if(currMinDistDp[j] != kLlInf) {
                // targetDist evaluates the base cost of completing 'j' robots
                // previously, offset by the prefix distance to maintain the sliding
                // window arithmetic.
                auto const targetDist{currMinDistDp[j] - prefDistPerRobot[j]};

                // Maintain monotonic increasing property: pop elements from the back if
                // they yield a worse (greater or equal) distance cost than our current
                // targetDist.
                while(head < tail && qDpMinDistAndRobot[tail - 1].first >= targetDist) {
                    --tail;
                }

                // Push the current valid state into the queue
                qDpMinDistAndRobot[tail++] = {targetDist, j};
            }
        }

        // Commit the computed state for the current factory to the main DP array
        rngs::copy(nextMinDistDp | vs::drop(1) | vs::take(robotTotCnt),
            currMinDistDp.begin() + 1);
    }

    // The answer is the min distance required to repair all robots (robotTotCnt)
    auto const minDist{currMinDistDp[robotTotCnt]};
    
    return minDist;
}
