// problem : https://leetcode.com/problems/walking-robot-simulation-ii/description
// submission : https://leetcode.com/problems/walking-robot-simulation-ii/submissions/1971916583
// solution post : https://leetcode.com/problems/walking-robot-simulation-ii/solutions/7816941/c-modern-readable-code-beats-9138-runtim-ixun

// Approach: 1D Perimeter Unrolling with Modulo Arithmetic
// time complexity O(1)
// space complexity O(1)
// runtime 18 ms, beats 91.38 %

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

class Robot {
public:
    Robot(
        int const width_,
        int const height_
    ) :
        // Storing maximum valid indices instead of raw dimensions simplifies boundary
        // calculations below
        mWidth{width_ - 1},
        mHeight{height_ - 1},
        mPerimeter{2 * (width_ - 1) + 2 * (height_ - 1)},
        mCurrPos{0},
        mHasMoved{false}
    {}
    
    auto step(int steps_) -> void {
        mHasMoved = true;
        // Modulo ensures the position strictly wraps around the 1D perimeter boundary
        mCurrPos = (mCurrPos + steps_) % mPerimeter;
    }
    
    [[nodiscard]]
    auto getPos() -> std::vector<int> {
        if(mCurrPos == 0) {
            return {0, 0};
        // Bottom edge coordinate resolution
        } else if(mCurrPos <= mWidth) {
            return {mCurrPos, 0}; 
        // Right edge coordinate resolution
        } else if(mCurrPos <= mWidth + mHeight) {
            auto const y{mCurrPos - (mWidth)};
            return {mWidth, y};
        // Top edge coordinate resolution
        } else if(mCurrPos <= 2 * (mWidth) + mHeight) {
            auto const x{mWidth - (mCurrPos - (mWidth + mHeight))};
            return {x, mHeight};
        // Left edge coordinate resolution
        } else {
            auto const y{mHeight - (mCurrPos - (2 * (mWidth) + mHeight))};
            return {0, y};
        }
    }
    
    [[nodiscard]]
    auto getDir() -> std::string {
        // The origin is a special edge case: the robot faces East only until its first
        // move. After that, it always faces South whenever it is at this cell
        if(mCurrPos == 0) {
            return mHasMoved ? kSouth : kEast;
        }
        if(mCurrPos <= mWidth) {
            return kEast;
        } else if(mCurrPos <= mWidth + mHeight) {
            return kNorth;
        } else if(mCurrPos <= 2 * (mWidth) + mHeight) {
            return kWest;
        } else {
            return kSouth;
        }
    }

private:
    static std::string const kEast;
    static std::string const kNorth;
    static std::string const kWest;
    static std::string const kSouth;

    int mWidth{};
    int mHeight{};
    int mPerimeter{};
    int mCurrPos{};
    bool mHasMoved;

};

std::string const Robot::kEast{"East"};
std::string const Robot::kNorth{"North"};
std::string const Robot::kWest{"West"};
std::string const Robot::kSouth{"South"};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */
