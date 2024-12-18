// problem : https://leetcode.com/problems/design-hashset/description/
// submission : https://leetcode.com/problems/design-hashset/submissions/1482273161
// solution post : https://leetcode.com/problems/design-hashset/solutions/6161156/c-modern-readable-code-by-cyberartist-mplg


// #include <vector>

// let 'n' be a quantity of values to map 
// 'm' - a data member 'base' value
// time complexity O(n / m)
// space complexity O(n)
// runtime 4 ms, beats 97.46 %
class MyHashSet {
public:
    void add(int key) {
        auto hashVal{hash(key)};
        if(cnt.at(hashVal) == hashVal) {
            return;
        } else if(cnt.at(hashVal) == free || cnt.at(hashVal) == usedBefore) {
            cnt.at(hashVal) = key;
        } else {
            auto idx{hashVal};
            while(++idx < cnt.size() && cnt.at(idx) != free &&
                cnt.at(idx) != usedBefore && cnt.at(idx) != hashVal)
            {}
            if(idx < cnt.size()) {
                cnt.at(idx) = key;
            } else {
                cnt.resize(cnt.size() * 2, free);
                cnt.at(idx) = key;
            }
        }
    }   
    void remove(int key) {
        auto hashVal{hash(key)};
        if(cnt.at(hashVal) == key) {
            cnt.at(hashVal) = usedBefore;
        } else {
            auto idx{hashVal};
            while(++idx < cnt.size() &&  cnt.at(idx) != free &&
                cnt.at(idx) != key
            ) {}
            if(idx < cnt.size() && cnt.at(idx) == key) {
                cnt.at(idx) = usedBefore;
            }
        }
    }
    bool contains(int const key) const {
        auto hashVal{hash(key)};
        if(cnt.at(hashVal) == key) {
            return true;
        } else {
            auto idx{hashVal};
            while(++idx < cnt.size() &&  cnt.at(idx) != free
                && cnt.at(idx) != key
            ) {}
            if(idx < cnt.size() && cnt.at(idx) == key) {
                return true;
            }
        }
        return false;
    }
    MyHashSet() :
        cnt(base, free)
    {}
private:
    int hash(int const key) const {
        return key % base;
    }
    int static constexpr free{-1};
    int static constexpr usedBefore{-2};
    int static constexpr base{100'000};
    std::vector<int> cnt;
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
