// problem : https://leetcode.com/problems/count-the-number-of-special-characters-ii/description
// submission : https://leetcode.com/problems/count-the-number-of-special-characters-ii/submissions/2014670627
// solution post : https://leetcode.com/problems/count-the-number-of-special-characters-ii/solutions/8297410/
//    c-modern-readable-code-beats-100-runtime-44t5

// Approach : Finite State Machine (FSM)
// Runtime : 27 ms, beats 100.00 %

// Complexity
// let 'n' be the number of
// complexity :  O(n)
// complexity : O(1), a character set size is a given small constant 26.

// import std;

class Solution final {
public:
    [[nodiscard]]
    static auto numberOfSpecialChars(std::string_view const word) -> int;

private:
    // Tracks progression towards satisfying letter appearance rules
    static enum class State : uint8_t {
        eNotSeen, eSeenLow, eSeenUp, eSeenLowUp, eInvalid
    };
    static auto constexpr kChrSetSz{26uz};
};

auto Solution::numberOfSpecialChars(std::string_view const word) -> int {
    namespace rngs = std::ranges;

    using enum State;

    auto const len{std::ssize(word)};
    // Insufficient length to form a valid pair
    if(len == 1) {
        return 0;
    }

    auto states{std::array<State, kChrSetSz>{}};
    
    // Process word according to problem rules using state transitions
    for(auto const chr: word) {
        auto const isLower{std::islower(chr)};
        auto const idx{chr - (isLower ? 'a' : 'A')};
        auto & state{states[idx]};

        if(isLower) {
            switch(state) {
                case eNotSeen:
                    state = eSeenLow;
                    break;
                case eSeenUp:
                case eSeenLowUp:
                    state = eInvalid;
                    break;
                case eInvalid:
                case eSeenLow:
                    break;
            }
        } else {
            switch(state) {
                case eNotSeen:
                    state = eSeenUp;
                    break;
                case eSeenLow:
                    state = eSeenLowUp;
                    break;
                case eSeenUp:
                case eSeenLowUp:
                case eInvalid:
                    break;
            }
        }
    }
    
    // Final count of letters maintaining the valid sequence
    return rngs::count(states, eSeenLowUp);
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
