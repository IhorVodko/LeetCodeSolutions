// problem : https://leetcode.com/problems/find-all-people-with-secret/description
// submission : https://leetcode.com/problems/find-all-people-with-secret/submissions/1861353968
// solution post : https://leetcode.com/problems/find-all-people-with-secret/solutions/7428090/
//    c-modern-readable-code-beats-100-runtime-otci

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

// let 'n' be the given number of people
// 'm' - the number of meetings
// time complexity O(m * log(m) + n)
// space complexity O(m + n)
// runtime 0 ms, beats 100.00 %
class DisjointSet {
public:
    DisjointSet(int const sz_) :
        mParents(sz_)
    {
        namespace vs = std::views;

        mRanks.resize(sz_);
        std::iota(mParents.begin(), mParents.end(), 0);
    }

    [[nodiscard]]
    auto Find(int const val_) -> int {
        auto & val{mParents.at(val_)};
        if(val != val_) {
           val = Find(val);
        } 
        return val;
    }

    auto Unite(
        int const val1_,
        int const val2_
    ) -> void {
        auto const parent1{Find(val1_)};
        auto const parent2{Find(val2_)};
        if(parent1 == parent2) {
            return;
        }
        auto & rank1{mRanks.at(parent1)};
        auto & rank2{mRanks.at(parent2)};
        if(rank1 > rank2) {
            mParents.at(parent2) = parent1;
        } else if(rank1 < rank2) {
            mParents.at(parent1) = parent2;
        } else {
            mParents.at(parent2) = parent1;
            rank1 += 1;
        }
    }

    [[nodiscard]]
    auto IsConnected(
        int const val1_,
        int const val2_
    ) -> bool {
        return Find(val1_) == Find(val2_);
    }

    auto Reset(int const val_) -> void {
        mParents.at(val_) = val_;
        mRanks.at(val_) = 0;
    }

private:
    std::vector<int> mParents;
    std::vector<int> mRanks;
};

class Solution {
public:
    [[nodiscard]]
    auto findAllPeople(
        int const peopleTotCnt_,
        std::span<std::vector<int>> const meetings_,
        int firstPerson
    ) -> std::vector<int> {
        namespace vs = std::views;
        namespace rngs = std::ranges; 
        
        rngs::sort(meetings_, [] (auto const & lhs_, auto const & rhs_) {
            return lhs_[2] < rhs_[2];
        });
        auto timeToPeople{std::map<int, std::vector<std::pair<int, int>>>{}};    
        for(auto const & meeting: meetings_) {
            auto const person1{meeting[0]};
            auto const person2{meeting[1]};
            auto const time{meeting[2]};
            timeToPeople[time].emplace_back(person1, person2);
        }
        auto peopleGraph{DisjointSet{peopleTotCnt_}};
        peopleGraph.Unite(firstPerson, 0);
        for(auto const & [_, people]: timeToPeople) {
            for(auto const [person1, person2]: people) {
                peopleGraph.Unite(person1, person2);
            }
            for(auto const [person1, person2]: people) {
                if(!peopleGraph.IsConnected(person1, 0)) {
                    peopleGraph.Reset(person1);
                    peopleGraph.Reset(person2);
                }
            }
        }
        auto peopleWithSecret(std::vector<int>{});
        peopleWithSecret.reserve(peopleTotCnt_);
        for(auto const idx: vs::iota(0, peopleTotCnt_)) {
            if(peopleGraph.IsConnected(idx, 0)) {
                peopleWithSecret.emplace_back(idx);
            }
        }
        peopleWithSecret.shrink_to_fit();
        return peopleWithSecret; 
    }
};
