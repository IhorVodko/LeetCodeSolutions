// problem : https://leetcode.com/problems/insert-delete-getrandom-o1/description/
// submission : https://leetcode.com/problems/insert-delete-getrandom-o1/submissions/1511383391
// solution post : https://leetcode.com/problems/insert-delete-getrandom-o1/solutions/6293760/c-modern-readable-code-beats-97-runtime-1vgcz

// #include <vector>
// #include <unordered_map>

// let 'n' be a number of stored elements in the set
// time complexity O(1)
// space complexity O(n)
// runtime 28 ms, beats 96.99 %
class RandomizedSet {
public:
    bool insert(int val) {
        if(valsToIdxs.contains(val)) {
            return false;
        }
        vals.emplace_back(val);
        return valsToIdxs.try_emplace(val, vals.size() - 1).second;
    }
    bool remove(int val) {
        if(!valsToIdxs.contains(val)) {
            return false;
        }
        if(vals.back() == val) {
            vals.pop_back();
            return valsToIdxs.erase(val);
        }
        vals.at(valsToIdxs.at(val)) = vals.back();
        valsToIdxs.at(vals.at(valsToIdxs.at(val))) = valsToIdxs.at(val);
        vals.pop_back();
        return valsToIdxs.erase(val);
    }
    int getRandom() const {
        assert(!vals.empty());
        return vals.at(std::rand() % vals.size());
    }
    RandomizedSet() {
        vals.reserve(static_cast<int>(10e5) * 2); 
    }
private:
    std::unordered_map<int, size_t> valsToIdxs;
    std::vector<int> vals;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
