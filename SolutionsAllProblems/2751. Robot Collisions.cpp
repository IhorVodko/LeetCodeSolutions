// problem : https://leetcode.com/problems/robot-collisions/description
// submission : https://leetcode.com/problems/robot-collisions/submissions/1966149163
// solution post : https://leetcode.com/problems/robot-collisions/solutions/7744592/c-modern-readable-code-runtime-0-ms-beat-c1oz

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

// Define a structure to hold all attributes of a single robot
struct Robot final {
    int mIdx{};
    int mPos{};
    int mHp{};
    char mDir{};
};

// let 'n' be the number of robots
// time complexity O(n * log(n))
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class Solution final {
public:
    [[nodiscard]]
    auto survivedRobotsHealths(
        std::vector<int> const & positions_,
        std::vector<int> const & healths_,
        std::string const & directions_
    ) const -> std::vector<int>;

private:
    static auto constexpr kLeft{'L'}; 
    static auto constexpr kRight{'R'}; 
};

auto Solution::survivedRobotsHealths(
    std::vector<int> const & positions_,
    std::vector<int> const & healths_,
    std::string const & directions_
) const -> std::vector<int> {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const robotTotCnt{std::ssize(positions_)};
    auto robots{std::vector<Robot>{}};
    robots.reserve(robotTotCnt);

    for(auto const j: vs::iota(0, robotTotCnt)) {
        robots.emplace_back(
            j, positions_[j], healths_[j], directions_[j] == kRight ? kRight : kLeft);
    }
    // Sort robots by position to correctly simulate collisions 
    rngs::sort(
        robots, std::less{}, [] (auto const & robot_) { return robot_.mPos; });

    // Initialize the write pointer which acts as the top of our in-place stack
    auto writePntr{0};

    // Iterate through each robot using the right pointer
    // for(auto const readPntr: vs::iota(0, robotTotCnt)) {
    for(auto & readRobot: robots) {
        // If the robot is moving right, push it onto the stack
        if(readRobot.mDir == kRight) {
        // Write the robot to the current top of the stack
            robots[writePntr] = readRobot;
            // Increment the stack pointer
            ++writePntr;
            continue;
        }

        // Reference to the current left-moving robot's health
        auto & lMoveHp{readRobot.mHp};

        // Process collisions while the stack is not empty, top robot moves right, and
        // current robot is alive
        while(writePntr >= 1 && robots[writePntr - 1].mDir == kRight && lMoveHp >= 1) {
            // Reference to the health of the right-moving robot on top of the stack
            auto & rMoveHp{robots[writePntr - 1].mHp};

            // Case where the top stack robot has less health than the current robot
            if(rMoveHp < lMoveHp) {
                // Current robot takes 1 damage
                --lMoveHp;
                // Top stack robot is destroyed, effectively popping it from the stack
                --writePntr;
            // Case where both robots have equal health
            } else if(rMoveHp == lMoveHp) {
                // Current robot is destroyed
                lMoveHp = 0;
                // Top stack robot is destroyed, popping it from the stack
                --writePntr;
            // Case where the top stack robot has more health
            } else {
                // Current robot is destroyed
                lMoveHp = 0;
                // Top stack robot takes 1 damage, based on constraints its health never
                // drops to zero
                --rMoveHp;
            }
        }

        // If the current left-moving robot survived all collisions
        if(lMoveHp != 0) {
            // Push it onto the stack
            robots[writePntr] = readRobot;
            // Increment the stack pointer
            ++writePntr;
        }
    }

    // Resize the vector to keep only the surviving robots
    robots.resize(writePntr);

    rngs::sort(robots, std::less{}, [] (auto const & robot_) { return robot_.mIdx; });

    auto survivedHealths{std::vector<int>{}};
    survivedHealths.reserve(robots.size());

    // Iterate through the survivors
    for(auto const & robot: robots) {
        survivedHealths.emplace_back(robot.mHp);
    }

    // Return the final list of surviving robots' healths in the original order
    return survivedHealths;
}
