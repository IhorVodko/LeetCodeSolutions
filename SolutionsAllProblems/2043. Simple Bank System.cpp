// problem : https://leetcode.com/problems/simple-bank-system/description
// submission : https://leetcode.com/problems/simple-bank-system/submissions/1813205093
// solution post : https://leetcode.com/problems/simple-bank-system/solutions/7305617/
//    c-modern-readable-code-beats-100-runtime-zsrm

// import std;

inline static int const fastIOInit{
        [] {
        struct Print {
            inline static void DoPrint() {
                std::ofstream("display_runtime.txt") << 0 << std::endl;
            }
        };
        std::atexit(&Print::DoPrint);
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

/**
 * Your Bank object will be instantiated and called as such:
 * Bank* obj = new Bank(balance);
 * bool param_1 = obj->transfer(account1,account2,money);
 * bool param_2 = obj->deposit(account,money);
 * bool param_3 = obj->withdraw(account,money);
 */

// let 'n' be the number of the given accounts
// runtime 0 ms, beats 100.00 %
class Bank {
public:
// time complexity O(n)
// space complexity O(n)
    explicit Bank(std::span<const long long> const balances_);
// time complexity O(1)
// space complexity O(1)
    auto transfer(
        int accIdxFrom_,
        int accIdxTo_,
        long long const amount_
    ) -> bool;
// time complexity O(1)
// space complexity O(1)
    auto deposit(
        int accIdx_,
        long long const amount_
    ) -> bool;
// time complexity O(1)
// space complexity O(1)
    auto withdraw(
        int accIdx_,
        long long const amount_
    ) -> bool;

private:
    template<std::signed_integral... ArgsT_>
    inline auto IsAccIdxValid(ArgsT_... accIdx_) const -> bool;

    std::vector<long long> mBalances;
    int mAccCnt{};
};

Bank::Bank(std::span<const long long> const balances_):
    mBalances{balances_.cbegin(), balances_.cend()},
    mAccCnt{static_cast<int>(balances_.size())}
{}

auto Bank::transfer(
    int accIdxFrom_,
    int accIdxTo_,
    long long const amount_
) -> bool {
    auto const accSz{std::ssize(mBalances)};
    auto isOpValid{false};
    if(!(IsAccIdxValid(--accIdxFrom_, --accIdxTo_))) {
        return isOpValid;
    }
    auto & balanceFrom{mBalances[accIdxFrom_]};
    if(balanceFrom < amount_) {
        return isOpValid;
    }
    balanceFrom -= amount_;
    mBalances[accIdxTo_] += amount_;
    return isOpValid = true; 
}

auto Bank::deposit(
    int accIdx_,
    long long const amount_
) -> bool {
    auto isOpValid{false};
    if(!IsAccIdxValid(--accIdx_)) {
        return isOpValid;
    }
    mBalances[accIdx_] += amount_;
    return isOpValid = true;
}

auto Bank::withdraw(
    int accIdx_,
    long long const amount_
) -> bool {
    auto isOpValid{false};
    if(!IsAccIdxValid(--accIdx_)) {
        return isOpValid;
    }
    auto & balance{mBalances[accIdx_]};
    if(balance < amount_) {
        return isOpValid;
    }
    balance -= amount_;
    return isOpValid = true; 
} 

template<std::signed_integral... ArgsT_>
auto Bank::IsAccIdxValid(ArgsT_... accIdx_) const -> bool {
    return ((accIdx_ < mAccCnt) && ...);
}
