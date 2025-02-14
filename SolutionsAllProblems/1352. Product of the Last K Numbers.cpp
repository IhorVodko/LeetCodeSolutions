// problem : https://leetcode.com/problems/product-of-the-last-k-numbers/description/
// submission : https://leetcode.com/problems/product-of-the-last-k-numbers/submissions/1543111705
// solution post : https://leetcode.com/problems/product-of-the-last-k-numbers/solutions/6422705/
//     c-modern-readable-code-beats-100-runtime-5u2n

// #include <array>

namespace  Constants {
    auto constexpr maxSize{static_cast<size_t>(4 * 10e4 + 1)};
}

// let 'n' be a number of calls to 'add' method
// time complexity O(n)
// space complexity O(1), a constant value equals (4 * 10e4 + 1)
// runtime 4 ms, beats 99.74 %
class ProductOfNumbers {
public:
    void add(int const num) {
        if(num == 0) {
            size = 0;
        } else {
            prefixProducts.at(size + 1) = prefixProducts.at(size) * num;
            ++size;
        }
    }
    int getProduct(int const windowLenght) const {
        if(windowLenght > size) {
            return 0;
        }
        return prefixProducts.at(size) / prefixProducts.at(size - windowLenght);
    }
    ProductOfNumbers():
        size{0}
    {
        prefixProducts.at(size) = 1;
    }
private:
    size_t size;
    std::array<int, Constants::maxSize> prefixProducts;
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
