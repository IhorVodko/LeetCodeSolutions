// problem : https://leetcode.com/problems/minimum-jumps-to-reach-end-via-prime-teleportation/description
// submission : https://leetcode.com/problems/minimum-jumps-to-reach-end-via-prime-teleportation/submissions/1998418573
// solution post : https://leetcode.com/problems/minimum-jumps-to-reach-end-via-prime-teleportation/submissions/1998418573

// Approach : Optimized BFS with Precomputed Sieve and Implicit Graph Mapping
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the count of given numbers
// 'm' - maximum possible number
// complexity :  O(n + m * log(log(m)))
// complexity : O(n + m)

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

// Precompute Eratosthene's Sieve for fast prime numbers lookup
auto constexpr kMaxNum{1'000'000};
auto constexpr kFirstPrime{2};

auto giSieve{std::array<bool, kMaxNum + 1>{}};

auto kIsPrecomputed{[] () {
    giSieve.fill(true);
    giSieve[0] = false;
    giSieve[1] = false;

    for(auto prime{kFirstPrime}; prime * prime <= kMaxNum; ++prime) {
        if(!giSieve[prime]) {
            continue;
        }

        for(auto num{prime * prime}; num <= kMaxNum; num += prime) {
            giSieve[num] = false;
        }
    }

    return true;
}()};

} // namespace 

class Solution final {
public:
    using numsT = std::vector<int>;

    [[nodiscard]]
    auto minJumps(numsT const & nums_) const -> int;

private:
    [[nodiscard]]
    auto DoBfs(
        numsT & mostRecentIdxArr,
        numsT const & nextIdxArr,
        numsT const & nums_,
        int const maxNum
    ) const -> int;
};

auto Solution::minJumps(numsT const & nums_) const -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    // Edge case
    if(nums_.size() == 1) {
        return 0;
    }

    auto const maxNum{*rngs::max_element(nums_)};
    auto const numsSz{std::ssize(nums_)};
    auto mostRecentIdxArr{numsT(maxNum + 1, -1)};
    auto nextIdxArr{numsT(numsSz, -1)};

    // Flatten linked list to map values to destinantion jump indices
    for(auto const currI: vs::iota(0, numsSz)) {
        auto & mostRecentI{mostRecentIdxArr[nums_[currI]]};
        nextIdxArr[currI] = mostRecentI;
        mostRecentI = currI;
    }

    auto const minJmpsCnt{DoBfs(mostRecentIdxArr, nextIdxArr, nums_, maxNum)};

    return minJmpsCnt;
}

auto Solution::DoBfs(
    numsT & mostRecentIdxArr,
    numsT const & nextIdxArr,
    numsT const & nums_,
    int const maxNum
) const -> int {
    auto const numsSz{std::ssize(nums_)};
    auto isSeenPrimeArr{std::vector<bool>(maxNum + 1)};

    auto isSeenIdxArr{std::vector<bool>(numsSz)};
    isSeenIdxArr[0] = true;

    auto qNums{std::queue<int>{}};
    qNums.emplace(0);

    auto jmpsCnt{0};
    while(!qNums.empty()) {
        auto levelSz{std::ssize(qNums)};

        while(levelSz-- > 0) {
            auto const currI{qNums.front()};
            qNums.pop();

            if(currI == numsSz - 1) {
                return jmpsCnt;
            }

            // 1. Adjecent step forward
            if( auto const nextI{currI  + 1};
                nextI < numsSz && !isSeenIdxArr[nextI]
            ) {
                isSeenIdxArr[nextI] = true;
                qNums.emplace(nextI);
            }

            // 2.Adjecent step backward
            if( auto const prevI{currI - 1};
                prevI >= 0 && !isSeenIdxArr[prevI]
            ) {
                isSeenIdxArr[prevI] = 1;
                qNums.emplace(prevI);
            }

            // 3. Prime teleportation
            if( auto const currNum{nums_[currI]};
                giSieve[currNum] && ! isSeenPrimeArr[currNum]
            ) {
                isSeenPrimeArr[currNum] = true;

                for(auto mult{currNum}; mult <= maxNum; mult += currNum) {
                    auto idx{mostRecentIdxArr[mult]};

                    while(idx != -1) {
                        if(!isSeenIdxArr[idx]) {
                            isSeenIdxArr[idx] = true;
                            qNums.emplace(idx);
                        }

                        idx = nextIdxArr[idx];
                    }

                    // Clear bucket to avoid redundant inner-iterations
                    mostRecentIdxArr[mult] = -1;
                }
            }
        }

        ++jmpsCnt;
    }

    // Safety fallback, not reachable
    return -1;     
}
