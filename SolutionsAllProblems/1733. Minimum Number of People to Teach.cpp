// problem : https://leetcode.com/problems/minimum-number-of-people-to-teach/description
// submission : https://leetcode.com/problems/minimum-number-of-people-to-teach/submissions/1766216746
// solution post : https://leetcode.com/problems/minimum-number-of-people-to-teach/solutions/7175963/
//    c-modern-readable-code-by-cyberartist-99a6

// #include <algorithms>
// #include <vector>

class Solution {
public:
    using languagesT = std::vector<int>;
    using friends = std::vector<int>;
// let 'p' be a count of the given friend pairs
// 'l' -languages given
// time complexity O(p * l)
// space complexity O(p + l)
// runtime 35 ms, beats 81.18 %
    [[nodiscard]]
    int minimumTeachings(
        int const languagesCount_,
        std::vector<languagesT> & languagesByUsers_,
        std::vector<friends> const & friendships_
    ) const;
};

int Solution::minimumTeachings(
    int const languagesCount_,
    std::vector<languagesT> & languagesByUsers_,
    std::vector<friends> const & friendships_
) const {
    namespace ranges = std::ranges;
    auto friendsNoComm{std::unordered_set<int>{}};
    auto commonLangs{std::vector<int>{}};
    for(auto & langs: languagesByUsers_) {
        ranges::sort(langs);
    }
    auto langToLearnCnts{std::vector<int>(languagesCount_ + 1, 0)};
    auto const processUser{
        [&] (auto const user_) {
            friendsNoComm.emplace(user_);
            for(auto lan: languagesByUsers_.at(user_)) {
                ++langToLearnCnts.at(lan);
            }
        }
    };
    for(auto const & friends: friendships_) {
        auto const user1{friends.at(0) - 1};
        auto const user2{friends.at(1) - 1};
        commonLangs.clear();
        auto  & langs1{languagesByUsers_.at(user1)};
        auto  & langs2{languagesByUsers_.at(user2)};
        ranges::set_intersection(
            langs1,
            langs2,
            std::back_inserter(commonLangs)
        );
        if(!commonLangs.empty()) {
            continue;
        }
        if(!friendsNoComm.contains(user1)) {
            processUser(user1);
        }
        if(!friendsNoComm.contains(user2)) {
            processUser(user2);
        }
    }
    auto langToLearnMaxCnt{*ranges::max_element(langToLearnCnts)};
    auto const minUsersToTeachCnt{friendsNoComm.size() - langToLearnMaxCnt};
    return minUsersToTeachCnt;
}
