// problem : https://leetcode.com/problems/kth-largest-element-in-an-array/description/
// submission : https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/1570460190
// solution post : https://leetcode.com/problems/kth-largest-element-in-an-array/solutions/6524965/
//     c-modern-readable-code-by-cyberartist-enhs

// #include <algorithm>
// #include <queue>
// #include <vector>

// let 'n' be a length of the given array
// 'k' - the k-th largest elemnt in the array
// time complexity O(n * log(k))
// space complexity O(k)
// runtime 24 ms, beats 75.05 %
class Solution {
public:
    using HeapMinT = std::priority_queue<int, std::vector<int>,
        std::greater<int>>;
    int findKthLargest(
        std::vector<int> const & nums_,
        int const kThLargest_
    ) const {
        auto heapMin{HeapMinT{}};
        std::for_each(nums_.begin(), nums_.end(), Pred{heapMin, kThLargest_});
        return heapMin.top();
    }
private:
    class Pred{
    public:
        Pred(
            HeapMinT & heapMin,
            int const kThLargest_
        ):
            mHeapMin{heapMin},
            mKThLargest{kThLargest_}
        {}
        void operator()(int const num) {
            if(mHeapMin.size() < mKThLargest) {
                mHeapMin.emplace(num);
            } else if(mHeapMin.top() <= num) {
                mHeapMin.pop();
                mHeapMin.emplace(num);
            }

        }
    private:
        HeapMinT & mHeapMin;
        int mKThLargest;
    };
};
