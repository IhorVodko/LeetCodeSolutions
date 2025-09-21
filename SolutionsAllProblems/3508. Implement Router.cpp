// problem : https://leetcode.com/problems/implement-router/description/
// submission : https://leetcode.com/problems/implement-router/submissions/1778353985
// solution post : https://leetcode.com/problems/implement-router/solutions/7211765/
//    c-modern-readable-code-optimal-time-comp-9v3c

// import std;

/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */

// let 'n' be a number of calls to the class
// let 'm' be a rooter memory limit
// time complexity O(m * log(n))
// space complexity O(m)
// runtime 243 ms, beats 74.66 %
class Router {
public:
// time complexity O(1))
// space complexity O(1)
    explicit Router(int const memoryLimit_);
// time complexity O(1)
// space complexity O(1)
    auto addPacket(
        int const source_,
        int const dest_,
        int const timeStamp_
    ) -> bool;
// time complexity O(1)
// space complexity O(1)
    [[nodiscard]]
    auto forwardPacket() -> std::vector<int>;
// time complexity O(log(m))
// space complexity O(1)
    [[nodiscard]]
    auto getCount(
        int const dest_,
        int const startTime_,
        int const endTime_
    ) const -> int;

private:
    using packetT = std::array<int, 3>;

    struct PacketHash {
        auto operator()(
            packetT const & packet_
        ) const noexcept -> std::size_t;
    };

    inline auto CheckInvariant() const -> void;

    static inline bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
    std::unordered_set<packetT, PacketHash> mPacketsSet;
    std::queue<packetT> mPacketsQueue;
    std::unordered_map<int, std::deque<int>> mDestToTimestamp;
    int const mMemoryLimit;
};

Router::Router(int const memoryLimit_):
    mMemoryLimit{memoryLimit_}
{
    if(memoryLimit_ <= 1) {
        throw std::invalid_argument{""};
    }
}

auto Router::addPacket(
    int const source_,
    int const dest_,
    int const timeStamp_
) -> bool {
    CheckInvariant();
    auto const packet{packetT{source_, dest_, timeStamp_}};
    if(mPacketsSet.contains(packet)) {
        return false;
    }
    if(mPacketsSet.size() == mMemoryLimit) {
        auto const & oldestPacket{mPacketsQueue.front()};
        if( mPacketsSet.erase(oldestPacket) == 0 ||
            mDestToTimestamp.at(oldestPacket.at(1)).empty()
        ) {
            throw std::out_of_range{""};
        }
        mDestToTimestamp.at(oldestPacket.at(1)).pop_front();
        if(mDestToTimestamp.at(oldestPacket.at(1)).empty()) {
            mDestToTimestamp.erase(oldestPacket.at(1));
        }
        mPacketsQueue.pop();
    }
    if(mPacketsSet.emplace(packet).second) {
        mDestToTimestamp[packet.at(1)].emplace_back(packet.at(2));
        mPacketsQueue.emplace(packet);
        return true;
    }
    return false;     
}

auto Router::forwardPacket() -> std::vector<int> {
    CheckInvariant();
    if(mPacketsSet.empty()) {
        return {};
    }
    auto const & packetRef{mPacketsQueue.front()};
    if( mPacketsSet.erase(packetRef) == 0 ||
        mDestToTimestamp.at(packetRef.at(1)).empty()
    ) {
        throw std::out_of_range{""};
    }
    mDestToTimestamp.at(packetRef.at(1)).pop_front();
    if( mDestToTimestamp.at(packetRef.at(1)).empty()) {
        mDestToTimestamp.erase(packetRef.at(1));
    }
    auto const packet{
        std::vector<int>(packetRef.cbegin(), packetRef.cend())};
    mPacketsQueue.pop();
    return packet;      
}

auto Router::getCount(
    int const dest_,
    int const startTime_,
    int const endTime_
) const -> int {
    CheckInvariant();
    if(!mDestToTimestamp.contains(dest_)) {
        return 0;
    }
    auto const & timeStamps{mDestToTimestamp.at(dest_)};
    auto const lbIt{ranges::lower_bound(timeStamps, startTime_)};
    auto const ubIt{ranges::upper_bound(timeStamps, endTime_)};
    auto const packetCnt{static_cast<int>(ranges::distance(lbIt, ubIt))};
    return packetCnt;
}

auto Router::PacketHash::operator()(
    packetT const & packet_
) const noexcept -> std::size_t {
    auto hash{size_t{0}};
    for(auto const val: packet_) {
        hash ^=
            std::hash<int>()(val) +
            0x9e3779b9 +
            (hash << 6) +
            (hash >> 2)
        ;
    }
    return hash;
}

auto Router::CheckInvariant() const -> void {
    if( mPacketsSet.size() != mPacketsQueue.size() ||
        mPacketsSet.size() > mMemoryLimit ||
        mDestToTimestamp.size() > mMemoryLimit
    ) {
        throw std::length_error{""};
    }        
}
