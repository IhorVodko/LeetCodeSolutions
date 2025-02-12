// problem : https://leetcode.com/problems/moving-average-from-data-stream/description/
// submission : https://leetcode.com/problems/moving-average-from-data-stream/submissions/1540370371
// solution post : https://leetcode.com/problems/moving-average-from-data-stream/solutions/6412448/
//     c-modern-readable-code-beats-100-runtime-o315

// #include <queue>

// let 'n' be a running window size
// time complexity O(1)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class MovingAverage {
public:
    double next(int const val) {
        queue.emplace(val);
        if(queue.size() <= size) {
            return (runningSum += val) / queue.size(); 
        }
        runningSum -= queue.front();
        queue.pop();
        return (runningSum += val) / queue.size();
    }
    explicit MovingAverage(size_t const size = 0):
        runningSum{0.},
        size{size}
    {}
private:
    std::queue<int> queue;
    double runningSum;
    size_t size;
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
