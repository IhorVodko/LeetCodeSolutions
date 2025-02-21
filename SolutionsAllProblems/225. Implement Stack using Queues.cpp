// problem : https://leetcode.com/problems/implement-stack-using-queues/description/
// submission : https://leetcode.com/problems/implement-stack-using-queues/submissions/1550763458
// solution post : https://leetcode.com/problems/implement-stack-using-queues/solutions/6451242/
//     c-modern-readable-code-beats-100-runtime-x1nw

// #include <queue>

// let 'n' be a queue size
// time complexity O(n)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class MyStack {
// let 'n' be a queue size
public:
    //time complexity O(n)
    //space complexity O(1)
    void push(int const x) {
        auto sz{queue.size()};
        queue.push(x);
        while(sz-- >= 1) {
            auto const num{queue.front()};
            queue.pop();
            queue.push(num);
        }
    }
    //time complexity O(1)
    //space complexity O(1)
    int pop() {
        auto const topNum{queue.front()};
        queue.pop(); 
        return topNum;
    }
    //time complexity O(1)
    //space complexity O(1)
    int top() {
       return queue.front(); 
    }
    //time complexity O(1)
    //space complexity O(1)
    bool empty() {
        return queue.empty();
    }
private:
    std::queue<int> queue;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
