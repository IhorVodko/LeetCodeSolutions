// problem : https://leetcode.com/problems/find-median-from-data-stream/description/
// submission : https://leetcode.com/problems/find-median-from-data-stream/submissions/1608728031
// solution post : https://leetcode.com/problems/find-median-from-data-stream/solutions/6657367/
//     c-modern-readable-code-optimal-time-comp-miqm

// #include <queue>
// #include <vector>

// let 'n' be a length of the given data stream
// time complexity O(log(n))
// space complexity O(n)
// runtime 69 ms, beats 38.38 %
class MedianFinder {
public:
    void addNum(int const num_) {
        mNumsLow.emplace(num_);
        mNumsHigh.emplace(mNumsLow.top());
        mNumsLow.pop();
        BalanceSizes(mNumsLow, mNumsHigh);
    }
    double findMedian() const {
        return mNumsLow.size() > mNumsHigh.size() ?
            mNumsLow.top() : (mNumsLow.top() + mNumsHigh.top()) * 0.5;
    }
    MedianFinder() {}
private:
    void BalanceSizes(
        auto & numsLow_,
        auto & numsHigh_
    ) {
        if(numsLow_.size() < numsHigh_.size()) {
            numsLow_.push(numsHigh_.top());
            numsHigh_.pop();
        }
    }
    std::priority_queue<int> mNumsLow;
    std::priority_queue<int, std::vector<int>, std::greater<>> mNumsHigh;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
