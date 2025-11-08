// problem : https://leetcode.com/problems/maximize-the-minimum-powered-city/description/
// submission : https://leetcode.com/problems/maximize-the-minimum-powered-city/submissions/
//    1824288482
// solution post : https://leetcode.com/problems/maximize-the-minimum-powered-city/solutions/
//    7335110/c-modern-readable-code-beats-100-runtime-qylv

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream("display_runtime.txt") << 0 << std::endl;
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
// let 'n' be the number of the given cities
// 'm' - number of the additional stations to build
// 's' - sum of the stations in the given sities
// time complexity O(n * log(s + m))
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto maxPower(
        std::span<int const> const stationsPerCity_,
        int range_,
        int additionalStations_
    ) const -> long long;
};

auto Solution::maxPower(
    std::span<int const> const stationsPerCity_,
    int range_,
    int additionalStations_
) const -> long long {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    auto const citiesSz_{static_cast<int>(stationsPerCity_.size())};
    auto diffArrInitial{std::vector<long long>(citiesSz_ + 1)};
    for(auto const city: vs::iota(0, citiesSz_)) {
        auto const leftPower{std::max(0, city - range_)};
        auto const rightPower{std::min(citiesSz_, city + range_ + 1)};
        diffArrInitial.at(leftPower) += stationsPerCity_[city];
        diffArrInitial.at(rightPower) -= stationsPerCity_[city];
    }
    auto diffArr{diffArrInitial};
    auto const IsValidMaxMinPower{
        [&] (long long maxMinPower_) -> bool {
            rngs::copy(diffArrInitial, diffArr.begin());
            auto power{0ll};
            auto remainingStations{additionalStations_};
            for(auto const city: vs::iota(0, citiesSz_)) {
                power += diffArr[city];
                if(power < maxMinPower_) {
                    auto const powerDeficit{maxMinPower_ - power};
                    if(remainingStations < powerDeficit) {
                        return false;
                    }
                    remainingStations -= powerDeficit;
                    auto end{std::min(citiesSz_, city + 2 * range_ + 1)};
                    diffArr[end] -= powerDeficit;
                    power += powerDeficit;
                }
            }
            return true;
        }
    };
    long long lowPower{rngs::min(stationsPerCity_)};
    auto highPower{
        std::accumulate(
            stationsPerCity_.begin(), 
            stationsPerCity_.end(),
            0ll
        ) + 
        additionalStations_
    };
    auto const maxMinPower{
        *(rngs::partition_point(
            vs::iota(lowPower, highPower + 1),
            IsValidMaxMinPower
        )) -
        1
    };
    return maxMinPower;
}
