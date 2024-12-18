// problem : https://leetcode.com/problems/design-hashmap/description/
// submission : https://leetcode.com/problems/design-hashmap/submissions/1482365806
// solution post : https://leetcode.com/problems/design-hashmap/solutions/6161463/c-modern-readable-code-by-cyberartist-7em1


// #include <array>
// #include <list>


// let 'n' be a lenght of range of keys 
// 'm' - a data member 'keySpace' length
// time complexity O(n / m)
// space complexity O(n)
// runtime 15 ms, beats 87.71 %
class MyHashMap {
public:
    void put(
        int const key,
        int const value
    );
    void remove(int const key);
    int get(int const key) const;
private:
    class Bucket {
    public:
        void put(
            int const key,
            int const value
        );
        void remove(int const key);
        int get(int const key) const;
    private:
        using itT = std::list<std::pair<int, int>>::iterator;
        using itConstT =  std::list<std::pair<int, int>>::const_iterator;
        itT find(int const key);
        itConstT find(int const key) const;
        std::list<std::pair<int, int>> bckt;
    };
    int hash(int const key) const;
    auto static constexpr keySpace{2069};
    std::array<Bucket, keySpace> cntnr;
};

void MyHashMap::put(
    int const key,
    int const value
) {
    cntnr.at(hash(key)).put(key, value);
}
void MyHashMap::remove(int const key) {
    cntnr.at(hash(key)).remove(key);
}
int MyHashMap::get(int const key) const {
    return cntnr.at(hash(key)).get(key);
}
int MyHashMap::hash(int const key) const {
    return key % keySpace;
}
void MyHashMap::Bucket::put(
    int const key,
    int const value
) {
    std::list<std::pair<int, int>>::iterator elem{find(key)};
    if(elem == bckt.end()) {
        bckt.push_front({key, value});
        return;
    }
    elem->second = value;
}
void MyHashMap::Bucket::remove(int const key) {
    auto elem{find(key)};
    if(elem != bckt.end()) {
        bckt.erase(elem);
    }
}
int MyHashMap::Bucket::get(int const key) const {
    auto elem{find(key)};
    return elem == bckt.cend() ? -1 : elem->second;
}
MyHashMap::Bucket::itT MyHashMap::Bucket::find(int const key)
{
    for(auto elem{bckt.begin()}, end{bckt.end()}; elem != end; ++elem) {
        if(elem->first == key) {
            return elem;
        }
    }
    return bckt.end();
}
MyHashMap::Bucket::itConstT MyHashMap::Bucket::find(int const key) const {
    for(auto elem{bckt.cbegin()}, end{bckt.cend()}; elem != end; ++elem) {
        if(elem->first == key) {
            return elem;
        }
    }
    return bckt.cend();
}
/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
