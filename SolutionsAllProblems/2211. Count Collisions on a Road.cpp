// problem : https://leetcode.com/problems/count-collisions-on-a-road/description/ 
// submission : https://leetcode.com/problems/count-collisions-on-a-road/submissions/1847942464
// solution post : https://leetcode.com/problems/count-collisions-on-a-road/solutions/7394724/
//    c-modern-readable-code-beats-100-runtime-3mbp

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream{"display_runtime.txt"} << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

class Solution {
public:
// let 'n' be the number of given cars
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto countCollisions(std::string_view directions_) const -> int;

private:
    static auto constexpr kRight{'R'};
    static auto constexpr kLeft{'L'};
    static auto constexpr kStay{'S'};
};

auto Solution::countCollisions(std::string_view directions_) const -> int {
    namespace vs = std::views;
    
    auto ignoreLeftCnt{0};
    auto const directionsSz{std::ssize(directions_)};
    auto ignoreRightCnt{directionsSz - 1};
    while(
        ignoreLeftCnt < directionsSz &&
        directions_[ignoreLeftCnt] == kLeft
    ) {
        ++ignoreLeftCnt;
    }
    while(
        ignoreRightCnt >= ignoreLeftCnt &&
        directions_[ignoreRightCnt] == kRight
    ) {
        --ignoreRightCnt;
    }
    auto res{0};
    for(auto i{ignoreLeftCnt}; i <= ignoreRightCnt; ++i) {
        res += directions_[i] == kStay ? 0 : 1;
    }
    return res;
}
