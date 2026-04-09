// problem : https://leetcode.com/problems/xor-after-range-multiplication-queries-ii/description
// submission : https://leetcode.com/problems/xor-after-range-multiplication-queries-ii/submissions/1973651956
// solution post : https://leetcode.com/problems/xor-after-range-multiplication-queries-ii/solutions/7845641/
//    c-modern-readable-code-beats-100-runtime-nuqk

// Approah : Square Root Decomposition with Multiplicative Difference Array
// Runtime : 0 ms, beats 100.00 %

// Complexity
// let 'n' be the length of the array of nubmers
// 'm' - number of queries
// time : O(n * sqrt(n) + q * sqrt(n) + q * log(q)) 
// space : O(n * sqrt(n) + q) 

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
    template<typename T>
    using jaggedArrT = std::vector<std::vector<T>>;

    [[nodiscard]]
    auto xorAfterQueries(
        std::vector<int> & nums_,
        std::vector<std::vector<int>> const & queries_
    ) -> int;

private:

    // Represents a sweep-line event for the multiplicative difference array. When
    // processing small step sizes, elements are grouped into sub-sequences based on
    // their remainder (index % step). This struct schedules when to start multiplying
    // and when to undo the multiplication (using a modular inverse) within a specific
    // sub-sequence.
    struct Event final {
        // The virtual (normalized) index within the specific sub-sequence. Calculated
        // as: (real_index - remainder) / step.
        int mVirtIdx{};
        // The multiplier to apply to the running total. This will be the actual
        // multiplier at the start of a range, or its modular multiplicative inverse at
        // the end of a range to "divide" it out.
        int mMult{};
    };

    // Calculates the modular multiplicative inverse using Fermat's Little Theorem
    [[nodiscard]]
    auto DoBinExp(ll base_) const noexcept -> int;

    static auto constexpr kMod{1'000'000'007};
};

auto Solution::xorAfterQueries(
    std::vector<int> & nums_,
    std::vector<std::vector<int>> const & queries_
) -> int {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    using eventsT = std::vector<Event>;

    auto const numsSz{std::ssize(nums_)};
    // The square root threshold for decomposing the step queries
    auto const stepPivot{static_cast<int>(std::ceil(std::sqrt(numsSz)))};
    // jagged array (3D vector) for sweep-line: jaggedArrOfEvents[step][remainder]
    // contains a list of {virtual_index, multiplier}
    auto jaggedArrOfEvents{jaggedArrT<eventsT>(stepPivot + 1)};
    jaggedArrOfEvents.reserve(stepPivot);

    // Initialize the jaggedArrOfEvents array layers for all possible small steps
    // (1 to stepPivot)
    for(auto const step: vs::iota(1, stepPivot + 1)) {
        // Resize the inner vector to hold buckets for all possible remainders modulo
        // 'step'
        jaggedArrOfEvents[step].resize(step);
    }

    for(auto const & query: queries_) {
        // Extract query parameters: real left index, real right index, step size, and
        // the multiplier
        auto const realL{query[0]};
        auto const realR{query[1]};
        auto const step{query[2]};
        auto const mult{query[3]};

        // If the step is large (greater than sqrt(N)), process elements directly to
        // avoid overhead
        if(step > stepPivot) {
            for(auto const idx: vs::iota(realL, realR + 1) | vs::stride(step)) {
                nums_[idx] = (static_cast<ll>(nums_[idx]) * mult)  % kMod;
            }
        // If the step is small, use a multiplicative difference array approach to
        // schedule updates
        } else {
            // The remainder bucket to group elements that fall on this specific sequence
            auto const rmndr{realL % step};
            // Calculate the virtual start (virtL) and end (virtR) indices within this sequence bucket
            auto const virtL{(realL - rmndr) / step};
            auto const virtR{(realR - rmndr) / step};

            // Schedule the multiplication to start at index virtL
            jaggedArrOfEvents[step][rmndr].emplace_back(virtL, mult);

            // If the multiplication stops before the end of the array, schedule a
            // division to undo it
            if(virtR <= ((numsSz - rmndr - 1) / step - 1)) {
                // The modular inverse of the multiplier (effectively dividing by mult)
                auto const modMultInv{DoBinExp(mult)};
                // Schedule the inverse operation just after the last affected virtual
                // index
                jaggedArrOfEvents[step][rmndr].emplace_back(virtR + 1, modMultInv);
            }
        }
    }

    // Vector to hold compressed events in case multiple queries start/end at the
    // exact same index
    auto cmprssdEvents{eventsT{}};

    // Process all accumulated sweep-line events for the small steps
    for(auto const step: vs::iota(1, stepPivot + 1)) {
        // Iterate over all possible sequence remainders for the current step size
        for(auto const rmndr: vs::iota(0, step)) {
            // Get the list of scheduled events for this specific sequence
            auto & events{jaggedArrOfEvents[step][rmndr]};

            // Skip processing if no queries affected this sequence
            if(events.empty()) {
                continue;
            }

            cmprssdEvents.clear();
            cmprssdEvents.reserve(events.size());

            // Sort events by their virtual index so we process them in left-toright
            // order
            rngs::sort(events, std::less{},
                [] (auto const & event_) { return event_.mVirtIdx; });

            // Combine events occurring at the exact same virtual index
            for(auto const & event: events) {
                // If the current event happens at the same virtual index as the
                // previous, multiply their effects
                if(!cmprssdEvents.empty() &&
                    cmprssdEvents.back().mVirtIdx == event.mVirtIdx
                ) {
                    cmprssdEvents.back().mMult =
                        (static_cast<ll>(cmprssdEvents.back().mMult) * event.mMult)
                        % kMod;
                // Otherwise, add it to the compressed list as a new distinct event
                } else {
                    cmprssdEvents.emplace_back(event);
                }
            }

            // Running cumulative multiplier across the sequence, starting at 1
            auto cumMult{1ll};
            // Pointer to track our position in the compressed events list
            auto eventIdx{0};

            // Sweep across the actual array elements belonging to this remainder
            // sequence
            for(auto realIdx{rmndr}, virtIdx{0}; realIdx < numsSz;
                realIdx += step, ++virtIdx
            ) {
                // If we've reached the virtual index for the next event(s), update the
                // running multiplier
                while(eventIdx < cmprssdEvents.size() &&
                    cmprssdEvents[eventIdx].mVirtIdx == virtIdx
                ) {
                    cumMult = (cumMult * cmprssdEvents[eventIdx].mMult) % kMod;
                    ++eventIdx;
                }

                // Apply the accumulated running multiplier to the actual array element
                nums_[realIdx] = (nums_[realIdx] * cumMult) % kMod;
            }
        }
    }

    // The final XOR sum of the array by folding over it with bitwise XOR
    auto const xorVal{
        rngs::fold_left(nums_ | vs::drop(1), nums_.front(), std::bit_xor{})};

    return xorVal;
}

// Binary exponentiation to find the modular inverse
auto Solution::DoBinExp(ll base_) const noexcept -> int {
    auto exp{kMod - 2};
    auto modMultInv{1ll};
    for(; exp; exp /= 2) {
        if(exp % 2 != 0) {
            modMultInv = (modMultInv * base_) % kMod;
        };
        base_ = (base_ * base_) % kMod;
    }
    return modMultInv;
}
