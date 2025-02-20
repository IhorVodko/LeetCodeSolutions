// problem : https://leetcode.com/problems/implement-queue-using-stacks/description/
// submission : https://leetcode.com/problems/implement-queue-using-stacks/submissions/1550024396
// solution post : https://leetcode.com/problems/implement-queue-using-stacks/solutions/6448273/
//   c-modern-readable-code-beats-100-runtime-eak3

// #include <stack>

// let 'n' be a length of the queue
// time complexity O(n)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class MyQueue {
public:
    void push(int const x) {
        if(qSize == 0) {
            frontNum = x;
        }
        if(stack1.empty()) {
            frontNumSecond = x;
        }
        stack1.push(x);
        ++qSize;
    }
    int pop() {
        auto numTop{0};
        if(qSize == 1 && stack1.size() == 1) {
            numTop = stack1.top();
            stack1.pop();
        } else {
            if(stack2.empty()) {
                auto sz{0};
                while(++sz <= qSize) {
                    stack2.push(stack1.top());
                    stack1.pop();
                }
                stack1 = std::stack<int>{};
            } 
            numTop = stack2.top();
            stack2.pop();
            if(!stack2.empty()) {
                frontNum = stack2.top();
            } else if(!stack1.empty()) {
                frontNum = frontNumSecond;
            }
        }
        --qSize;
        return numTop;
    }
    int peek() {
        return frontNum;
    }
    bool empty() const {
        return qSize == 0;
    }
    MyQueue():
        qSize{0},
        frontNum{0},
        frontNumSecond{0}
    {}
private:
    size_t qSize;
    int frontNum;
    int frontNumSecond;
    std::stack<int> stack1;
    std::stack<int> stack2;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
