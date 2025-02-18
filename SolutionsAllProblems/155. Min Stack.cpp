// problem : https://leetcode.com/problems/min-stack/description/
// submission : https://leetcode.com/problems/min-stack/submissions/1547516524
// solution post : https://leetcode.com/problems/min-stack/solutions/6438269/
//     c-modern-readable-code-beats-100-runtime-pwna

// #include <vector>

// let 'n' be a number of calls to the class
// time complexity O(1)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class MinStack {
public:
    void push(int const val) {
        container.emplace_back(val);     
        if(minContainer.empty() || val < minContainer.back().first) {
            minContainer.emplace_back(std::make_pair(val, 1));
        } else if(val == minContainer.back().first) {
            ++minContainer.back().second;
        }
    }
    void pop() {
        if(container.back() == minContainer.back().first &&
            --minContainer.back().second == 0
        ) {
            minContainer.pop_back();
        }
        container.pop_back();
    }
    int top() const {
       return container.back(); 
    }
    int getMin() const {    
        return minContainer.back().first;
    }
private:
    std::vector<int> container;
    std::vector<std::pair<int, int>> minContainer;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
