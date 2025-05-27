// problem : https://leetcode.com/problems/first-unique-number/description/
// submission : https://leetcode.com/problems/first-unique-number/submissions/1646162198
// solution post : https://leetcode.com/problems/first-unique-number/solutions/6787204/
//    c-modern-readable-code-optimal-time-comp-hoc6

// #include <list>
// #include <vector>
// #include <unordered_map>

// let 'n' be a count of numbers to process
// time complexity O(n)
// space complexity O(n)
// runtime 274 ms, beats 20.20 %
class FirstUnique {
public:
    FirstUnique(std::vector<int> const & nums_) {
        for(auto const num: nums_) {
            add(num);
        } 
    }
    int showFirstUnique() {
        return mOrderedUniqueNums.empty() ? -1 : mOrderedUniqueNums.front();
    }
    void add(int const num_) {
        if(mNumToIsUnique.contains(num_)) {
            mNumToIsUnique.at(num_) = false;
            if(mNumUniqueToIdx.contains(num_)) {
                mOrderedUniqueNums.erase(mNumUniqueToIdx.at(num_));
                mNumUniqueToIdx.erase(num_);
            }
        } else {
            mNumToIsUnique[num_] = true;
            mOrderedUniqueNums.emplace_back(num_);
            mNumUniqueToIdx[num_] = std::prev(mOrderedUniqueNums.end());
        }
    }
private:
    std::list<int> mOrderedUniqueNums;
    std::unordered_map<int, decltype(mOrderedUniqueNums)::iterator>
        mNumUniqueToIdx;
    std::unordered_map<int, bool> mNumToIsUnique;
};

/**
 * Your FirstUnique object will be instantiated and called as such:
 * FirstUnique* obj = new FirstUnique(nums);
 * int param_1 = obj->showFirstUnique();
 * obj->add(value);
 */
