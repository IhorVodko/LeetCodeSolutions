// problem : https://leetcode.com/problems/design-linked-list/description/
// submission : https://leetcode.com/problems/design-linked-list/submissions/1515663316
// solution post : https://leetcode.com/problems/design-linked-list/solutions/6310701/c-modern-readable-code-by-cyberartist-1zhs

// #include <memory>

// let 'n' be a length of the given linked list
// time complexity O(n)
// space complexity O(n)
// runtime 69 ms, beats 5.07 % (implement doubly linked list to beat 100 % )
class MyLinkedList {
public:
    int get(int const index) const {
        if(!isValidIndex(index)) {
            return -1;
        }
        auto node{head};
        for(auto i{size_t{0}}; i < index + 1; ++i) {
            node = node->getNext();
        }
        return node->getVal();
    }
    void addAtHead(int const val) {
        addAtIndex(0, val);
    }
    void addAtTail(int const val) {
        addAtIndex(size, val);
    }
    void addAtIndex(
        int index,
        int const val
    ) {
        if(index > size) {
            return;
        }
        index = index < 0 ? 0 : index;
        auto node{head};
        for(auto i{size_t{0}}; i < index; ++i) {
            node = node->getNext();
        }
        node->setNext(std::make_shared<Node>(val, node->getNext()));
        ++size;
    }
    void deleteAtIndex(int const index) {
        if(!isValidIndex(index)) {
            return;
        }
        auto node{head};
        for(auto i{size_t{0}}; i < index; ++i) {
            node = node->getNext();
        }
        node->setNext(std::move(node->getNext()->getNext()));
        --size;
    }
    MyLinkedList():
        size{0},
        head{std::make_shared<Node>(-1)}
    {}    
private:
    bool isValidIndex(int const index) const {
        return 0 <= index && index < size;
    }
    class Node{
    public:
        int getVal() const {
            return val;
        }
        std::shared_ptr<Node> getNext() const {
            return next;
        }
        void setVal(int const val) {
            this->val = val; 
        }
        void setNext(std::shared_ptr<Node> && next) {
            this->next = next;
        }
        Node():
            val{0},
            next{nullptr}
        {}
        explicit Node(
            int const val,
            std::shared_ptr<Node> next = nullptr
        ) : 
            val{val},
            next{next}
        {} 
    private:
        int val;
        std::shared_ptr<Node> next;
    };
    size_t size;
    std::shared_ptr<Node> head;
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
