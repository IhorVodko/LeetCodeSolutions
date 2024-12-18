// problem : https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/description/
// submission : https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/submissions/1482308395
// solution post : https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/solutions/6161269/c-modern-readable-code-beats-100-runtime-d6ti


// #include <stack>
// #include <vector>


class Solution {
public:
    // let 'n' be a parameter 'prices' length
    // time complexity O(n)
    // space complexity O(n)
    // runtime 0 ms, beats 100.00 %
    std::vector<int> finalPrices(std::vector<int> & prices) const {
        using itT = std::remove_cvref<decltype(prices)>::type::iterator;
        auto stack{std::stack<itT>{}};
        for(auto price{prices.begin()}, end{prices.end()}; price < end;
            ++price
        ) {
            while(!stack.empty() && *stack.top() >= *price) {
                *stack.top() -= *price;
                stack.pop();    
            }
            stack.push(price);
        }
        return prices;
    }
};
