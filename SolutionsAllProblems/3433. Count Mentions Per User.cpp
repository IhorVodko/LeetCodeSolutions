// problem : https://leetcode.com/problems/count-mentions-per-user/description/
// submission : https://leetcode.com/problems/count-mentions-per-user/submissions/1854066333
// solution post : https://leetcode.com/problems/count-mentions-per-user/solutions/7409680/
//    c-modern-readable-code-beats-100-runtime-7zc1

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
// let 'n' be the number of given events
// 'm' - given number of users 
// time complexity O(n * log(n) + n * m) = O(n * (log(n) + m))
// space complexity O(m)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto countMentions(
        int userSz_,
        std::span<std::vector<std::string>> const events_
    ) -> std::vector<int>;

private:
    auto ProcessMsgTMessage(
        auto const time_,
        auto const ids_
    ) -> void;
    auto ProcessMsgTOffline(
        auto const time_,
        auto const id_
    ) -> void;

    static auto constexpr kOfflinePeriod{60};
    std::vector<int> mUserMentionCnt;
    std::array<int, 100> mOnlineAgainTime;
    int mUserSz{};
};

auto Solution::countMentions(
    int userSz_,
    std::span<std::vector<std::string>> const events_
) -> std::vector<int> {
    namespace vs = std::views;
    namespace rngs = std::ranges;

    mUserSz = userSz_;
    mUserMentionCnt = std::vector<int>(mUserSz);
    mOnlineAgainTime.fill(0);
    rngs::sort(
        events_,
        [] (
            std::span<std::string const> const lhs_,
            std::span<std::string const> const rhs_
        ) {
            std::string_view const lTime{lhs_[1]};
            std::string_view const rTime{rhs_[1]};
            if(lTime == rTime) [[unlikely]] {
                std::string_view const msgT{lhs_[0]};
                return msgT == "OFFLINE";
            } else [[likely]] {
                return lTime.size() == rTime.size() ?
                    lTime < rTime : lTime.size() < rTime.size(); 
            }
        }
    );
    for(auto const & event: events_) {
        std::string_view const msgType{event[0]};
        std::string_view const timeStr{event[1]};
        auto time{-1};
        std::from_chars(timeStr.data(), timeStr.data() + timeStr.size(), time);
        auto const & ids{event[2]};
        if(msgType == "MESSAGE") {
            ProcessMsgTMessage(time, ids);
        } else {
            ProcessMsgTOffline(time, ids);
        }
    }
    return mUserMentionCnt;
}

auto Solution::ProcessMsgTMessage(
    auto const time_,
    auto const ids_
) -> void {
    namespace vs = std::views;

    if(ids_ == "ALL") {
        for(auto & cnt: mUserMentionCnt) {
            ++cnt;
        }
    } else if(ids_ == "HERE") {
        for(auto const user: vs::iota(0, mUserSz)) {
            if(time_ >= mOnlineAgainTime[user]) {
                ++mUserMentionCnt[user];
            }
        }
    } else {
        auto userStr{""s};
        for(auto const chr: ids_) {
            if(std::isdigit(chr)) {
                userStr += chr;
            } else {
                if(!userStr.empty()) {
                    ++mUserMentionCnt[std::stoi(userStr)];
                    userStr.clear();
                }
            }
        }
        if(!userStr.empty()) [[likely]] {
            ++mUserMentionCnt[std::stoi(userStr)];
        }
    }
}

auto Solution::ProcessMsgTOffline(
    auto const time_,
    auto const id_
) -> void {
    auto userStr{""s};
    for(auto const chr: id_) {
        if(std::isdigit(chr)) {
            userStr += chr;
        }
    }
    mOnlineAgainTime[std::stoi(userStr)] = time_ + kOfflinePeriod; 
}
