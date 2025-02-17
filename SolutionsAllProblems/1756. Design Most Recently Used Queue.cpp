// problem : https://leetcode.com/problems/design-most-recently-used-queue/description/
// submission : https://leetcode.com/problems/design-most-recently-used-queue/submissions/1546243581
// solution post : https://leetcode.com/problems/design-most-recently-used-queue/solutions/6433529/
//     c-modern-readable-code-beats-90-runtime-qy9p8

// #include <algorithm>
// #include <vector>

// let 'n' be a size of the container
// time complexity O(n^(1/2))
// space complexity O(n)
// runtime 11 ms, beats 89.51 %
class MRUQueue {
public:
    int fetch(int const idx) {
        auto bucketIndex{std::upper_bound(index.begin(), index.end(), idx) -
            index.begin() - 1}; 
        auto element{data.at(bucketIndex).at(idx - index.at(bucketIndex))};
        data.at(bucketIndex).erase(data.at(bucketIndex).begin() + (idx -
            index.at(bucketIndex)));
        for(auto i{bucketIndex + 1}; i < index.size(); ++i) {
            --index.at(i);
        }
        if(data.back().size() >= bucketSize) {
            data.emplace_back(std::vector<int>{});
            index.emplace_back(totalElements);
        }
        data.back().emplace_back(element);
        if(data.at(bucketIndex).empty()) {
            data.erase(data.begin() + bucketIndex);
            index.erase(index.begin() + bucketIndex);
        }
        return element;
    }
    MRUQueue(int const size):
        totalElements{size},
        bucketSize{static_cast<int>(std::sqrt(size))}
    {
        for(auto number{1}; number <= size; ++number) {
            auto bucketIndex{(number - 1) / bucketSize};
            if(bucketIndex == data.size()) {
                data.emplace_back(std::vector<int>{});
                index.emplace_back(number);
            }
            data.back().emplace_back(number);
        }
    }
private:
    using Arr1 = std::vector<int>;
    using Arr2 = std::vector<std::vector<int>>;
    int totalElements;
    int bucketSize;
    Arr2 data;
    Arr1 index;
};

/**
 * Your MRUQueue object will be instantiated and called as such:
 * MRUQueue* obj = new MRUQueue(n);
 * int param_1 = obj->fetch(k);
 */
