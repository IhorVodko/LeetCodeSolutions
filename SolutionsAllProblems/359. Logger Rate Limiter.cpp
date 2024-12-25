// problem : https://leetcode.com/problems/logger-rate-limiter/description/
// submission : https://leetcode.com/problems/logger-rate-limiter/submissions/1488251319
// solution post : https://leetcode.com/problems/logger-rate-limiter/solutions/6186636/c-modern-readable-code-beats-96-runtime-14dcl

// #include <string>
// #include <unordered_map>

// let 'n' be a number of messages to process
// time complexity O(n)
// space complexity O(n)
// runtime 3 ms, beats 96.26 %
class Logger {
public:
    bool shouldPrintMessage(
        int const timestamp,
        std::string const message
    ) {
        auto const msgToNextAllowedTimestamp{
            msgsToNextAllowedTimestamps.find(message)};
        if(msgToNextAllowedTimestamp == msgsToNextAllowedTimestamps.end() ||
            timestamp >= msgToNextAllowedTimestamp->second
        ) {
            msgsToNextAllowedTimestamps[message] = timestamp + timeHalt;
            return true;
        }
        return false;
    }
private:
    auto static constexpr  timeHalt{10};
    std::unordered_map<std::string, int> msgsToNextAllowedTimestamps;
};

/*
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */
