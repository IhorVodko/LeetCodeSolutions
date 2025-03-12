// problem : https://leetcode.com/problems/kth-largest-element-in-a-stream/description/
// submission : https://leetcode.com/problems/kth-largest-element-in-a-stream/submissions/1571211142
// solution post : https://leetcode.com/problems/kth-largest-element-in-a-stream/solutions/6528056/
//     c-modern-readable-code-optimal-time-comp-52px

// #include <queue>
// #include <vector>

// let 'n' be a length of the given array 'nums'
// 'c' - number of calls to mehtod 'add'
// 'k' - kTh highest score to track
// time complexity O((n + c) * log(k))
// space complexity O(k)
// runtime 5 ms, beats 74.78 %
class KthLargest {
public:
    int add(int const num);
    KthLargest(
        int const kThLargest,
        std::vector<int> const & nums
    );
private:
    void UpdateHeap(int const num);
    std::priority_queue<int, std::vector<int>, std::greater<int>> mHeapMin;
    int const mKThLargest;
};

int KthLargest::add(int const num) {
    UpdateHeap(num);
    return mHeapMin.top();
}
KthLargest::KthLargest(
    int const kThLargest,
    std::vector<int> const & nums
):
    mKThLargest{kThLargest}
{
    for(auto const num: nums) {
        UpdateHeap(num);
    }
}
void KthLargest::UpdateHeap(int const num) {
    if(mHeapMin.size() < mKThLargest) {
        mHeapMin.emplace(num);
    } else if(mHeapMin.top() < num) {
        mHeapMin.pop();
        mHeapMin.emplace(num);
    }
}

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
