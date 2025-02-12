// problem : https://leetcode.com/problems/design-circular-queue/description/
// submission : https://leetcode.com/problems/design-circular-queue/submissions/1540344600
// solution post : https://leetcode.com/problems/design-circular-queue/solutions/6412355/
//     c-modern-readable-code-beats-100-runtime-1be2

// #include <vector>

// let 'n' be a size of the given queue
// time complexity O(1)
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
class MyCircularQueue {
public:
    bool enQueue(int const value) {
        if(isFull()) {
            return false;
        }
        idxTail = isEmpty() ? idxTail : ++idxTail % capacity;
        container.at(idxTail) = value;
        ++size;
        return true;
    }    
    bool deQueue() {
        if(isEmpty()) {
            return false; 
        } 
        idxHead = size == 1 ? idxHead : ++idxHead % capacity;
        --size;
        return true;
    }
    int Front() {
        return isEmpty() ? -1 : container.at(idxHead); 
    }
    int Rear() {
        return isEmpty() ? -1 : container.at(idxTail); 
    }
    bool isEmpty() const {
       return size == 0; 
    }
    bool isFull() const {
       return size == container.size(); 
    }
    explicit MyCircularQueue(size_t const capacity = 0):
        container(capacity, -1),
        capacity{capacity},
        idxHead{0},
        idxTail{0},
        size{0}
    {}
private:
    std::vector<int> container;
    size_t capacity;
    size_t idxHead;
    size_t idxTail;
    size_t size;
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */
