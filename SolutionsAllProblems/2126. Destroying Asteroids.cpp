// problem : https://leetcode.com/problems/destroying-asteroids/description
// submission : https://leetcode.com/problems/destroying-asteroids/submissions/2019138437
// solution post : https://leetcode.com/problems/destroying-asteroids/solutions/8306652/c-modern-readable-code-beats-100-runtime-l327

// Approach : Iterative Greedy Sweep
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the count of asteroids given
// 'M' maximum mass of the asteroid given
// complexity :  O(n * log(M))
// complexity : O(1), auxiliary space

// import std;

class Solution final {
public:
    using ll = long long;

    [[nodiscard]]
    static auto asteroidsDestroyed(
        int const planetMass_,
        std::vector<int> & asteroidMasses_
    ) -> bool;

private:
    static auto constexpr kDestroyedMass{0};
};

auto Solution::asteroidsDestroyed(
    int const planetMass_,
    std::vector<int> & asteroidMasses_
) -> bool {
    // Working mass
    auto planet{static_cast<ll>(planetMass_)};

    // Sweep logic to absorb accessible targets
    auto const CountDestroyedAsteroids{ [&] () -> int {
        auto destrCnt{0};

        for(auto & asteroid: asteroidMasses_) {
            // Bypass targets exceeding current capacity
            if(planet < asteroid) {
                continue;
            }

            // Assimilate target mass and nullify to prevent double counting
            planet += asteroid;
            asteroid = kDestroyedMass;
            ++destrCnt;
        }

        return destrCnt;
    }};

    // Continuously resweep until victory or deadlock
    for(auto    destrCntCurr{CountDestroyedAsteroids()},
                destrCntNext{0};
        destrCntCurr < asteroidMasses_.size();
        destrCntCurr = destrCntNext
    ) {
        destrCntNext = CountDestroyedAsteroids();

        // Identify deadlock state where no new targets are absorbable
        if(destrCntCurr == destrCntNext) {
            return false;
        }
    }

    // All asteroids are destroyed
    return true;
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
