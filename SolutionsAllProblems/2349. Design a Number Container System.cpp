// problem : https://leetcode.com/problems/design-a-number-container-system/description/
// submission : https://leetcode.com/problems/design-a-number-container-system/submissions/1538529295
// solution post : https://leetcode.com/problems/design-a-number-container-system/solutions/6404709/
//     c-modern-readable-code-beats-96-runtime-cuxa6

// #include <unordered_map>
// #include <unordered_set>

// let 'n' be a total number of unique indexes and numbers
// time complexity: 'change' method - O(n); 'find' method - O(1)
// space complexity: 'change' method - O(n); 'find' method - O(1)
// runtime 74 ms, beats 96.20 %
class NumberContainers {
public:
    void change(
        int const idx,
        int const newNum
    ) {
        if(auto const idxToOldNumIt{idxToNum.find(idx)};
            idxToOldNumIt != idxToNum.cend()
        ) {
            if(idxToNum.at(idx) == newNum) {
                return;
            }
            numToIdxs[newNum].emplace(idx); 
            auto const oldNum{idxToOldNumIt->second};
            numToIdxs.at(oldNum).erase(idx);
            if(numToIdxs.at(oldNum).empty()) {
                numToIdxs.erase(oldNum);                
            }
            idxToNum.at(idx) = newNum;
        }
        numToIdxs[newNum].emplace(idx);
        idxToNum[idx] = newNum;

    }
    int find(int const num) const {
        if(auto const numToIdxsIt{numToIdxs.find(num)};
            numToIdxsIt == numToIdxs.cend()
        ) {
            return -1;
        } else {
            return *numToIdxsIt->second.begin();
        }
    }
private:
    std::unordered_map<int, std::set<int>> numToIdxs;
    std::unordered_map<int, int> idxToNum;
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */
