// problem : https://leetcode.com/problems/walking-robot-simulation/description
// submission : https://leetcode.com/problems/walking-robot-simulation/submissions/1971679746
// Solution post : https://leetcode.com/problems/walking-robot-simulation/solutions/7813718/c-modern-readable-code-beats-100-runtime-aa8q

// let 'n' be the number of commands
// 'm' - number of obstacles
// time complexity O(n + m)
// space complexity O(m)
// runtime 0 ms, beats 100.00 %

// Approach name : Simulation with a Hash Set

// Algorithm: Simulation with Hash Set
// 1. Initialize an unordered set to store obstacles for O(1) lookups, using a custom
//      hash function.
// 2. Set the robot's starting position to the origin (0, 0) and its initial direction to
//      North.
// 3. Initialize a variable to track the maximum squared Euclidean distance reached
//      during the simulation.
// 4. Iterate sequentially through each command provided in the commands array.
// 5. If the command is -1, turn the robot 90 degrees clockwise by updating the direction
//      index.
// 6. If the command is -2, turn the robot 90 degrees counterclockwise by updating the
//      direction index.
// 7. If the command is a movement distance, process the movement step-by-step (one unit
//      at a time).
// 8. Calculate the intended next coordinate based on the current direction.
// 9. Check if this next coordinate exists in the obstacles hash set.
// 10. If an obstacle is detected, halt movement for the current command immediately.
// 11. If the path is clear, move the robot to the next coordinate.
// 12. After resolving a move command, calculate the squared distance of the current
//      position from the origin.
// 13. Update the maximum distance tracker if the newly calculated distance is greater.
// 14. Once all commands are processed, return the highest maximum squared distance
//      recorded.

// import std;
#include <memory_resource>

namespace {

auto constexpr kBuffSz{1024uz * 1024uz};
auto kBuff{std::array<std::byte, kBuffSz>{}};
// A monotonic buffer resource using the statically allocated array for fast
// memory allocation
auto gMemPool{std::pmr::monotonic_buffer_resource{kBuff.data(), kBuff.size()}};

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
    [[nodiscard]]
    auto robotSim(
        std::vector<int> const & commands_, 
        std::vector<std::vector<int>> const & obstacles_
    ) const -> int;

    // A custom hash functor for std::pair<int, int> to use in unordered
    // containers
    struct PositionHash final {
        [[nodiscard]]
        auto operator()(std::pair<int, int> const & pos_) const noexcept -> std::size_t;
    };

private:
    // The four cardinal directions: North, East, South, West respectively
    static auto constexpr kDirs{std::array<std::pair<int, int>, 4>{
        {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}}};
    // A prime multiplier for the custom position hash function
    static auto constexpr kHashMult{60'013};
};

auto Solution::robotSim(
    std::vector<int> const & commands_, 
    std::vector<std::vector<int>> const & obstacles_
) const -> int {
    namespace vs = std::views;

    // Reset the monotonic buffer resource to its initial state, clearing previous
    // allocations
    gMemPool.release();
    // Create an unordered_set for obstacles using the custom hash and the custom memory
    // pool
    auto obstacles{std::pmr::unordered_set<std::pair<int, int>, PositionHash>{&gMemPool}};
    obstacles.reserve(obstacles_.size());

    for(auto const & obstacle: obstacles_) {
        obstacles.emplace(obstacle[0], obstacle[1]);
    }

    auto currPos{std::pair<int, int>{}};
    // Track the maximum squared Euclidean distance reached from the origin
    auto maxDist{0};
    auto dirIdx{0};

    for(auto const command: commands_) {
        if(command == -1) {
            // Update the direction index to the next clockwise direction
            dirIdx = (dirIdx + 1) % 4;
        } else if(command == -2) {
            // Update the direction index to the next counterclockwise direction
            dirIdx = (dirIdx + 3) % 4;

        // Otherwise, the command is to move forward by a specified number of units
        } else {
            auto const [offsetX, offsetY]{kDirs[dirIdx]};

            // Loop for the exact number of steps specified by the command
            for(auto const step: vs::iota(0, command)) {
                auto const [currX, currY]{currPos};
                auto const nextPos{
                    std::pair<int, int>{currX + offsetX, currY + offsetY}};

                if(obstacles.contains(nextPos)) {
                    // Stop moving forward for this command if an obstacle is hit
                    break;
                } else {
                    currPos = std::move(nextPos);
                }
            }

            auto const [x, y]{currPos};
            // Calculate the squared Euclidean distance of the current position from the
            // origin
            auto const curDist{x * x + y * y};
            maxDist = std::max(maxDist, curDist);
        }
    }

    return maxDist;
}

auto Solution::PositionHash::operator()(
    std::pair<int, int> const & pos_
) const noexcept -> std::size_t {
    return pos_.first + kHashMult * pos_.second;
}
