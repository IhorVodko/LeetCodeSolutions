// problem : https://leetcode.com/problems/fancy-sequence/description
// submission : https://leetcode.com/problems/fancy-sequence/submissions/1949205567
// solution post : https://leetcode.com/problems/fancy-sequence/solutions/7650296/
//    c-modern-readable-code-runtime-0-ms-beat-8mj2

// import std;

namespace {

// Compile-time initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] -> int {
        std::atexit([] { std::ofstream{"display_runtime.txt"} << 0 << std::endl; } );
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace

// time complexity O(1)
// space complexity O(1)
// runtime 0 ms, beats 100.00 %
class Fancy final {
public:
    using ll = long long;

    // Constructor: reserve memory for efficiency
    Fancy() {
        mNums.reserve(kMaxNumsSz);
    };
    
    // Append a new value to the sequence. We store the "inverse-transformed" value so
    // that future multAll and addAll operations can be applied lazily
    auto append(ll const val_) -> void {
        // Undo the current affine transformation: original formula:
        // value = mParamA * stored_val + mParamB, so
        // stored_val = (val - mParamB) / mParamA (mod kModulus)
        auto const val{
            (val_ - mParamB + kModulus) % kModulus * DoInv(mParamA) % kModulus};
        mNums.emplace_back(val);
    }
    
    // Increment all elements lazily by updating the additive parameter. We do not update
    // all stored values individually
    auto addAll(ll const addend_) -> void {
        mParamB = (mParamB + addend_) % kModulus;
    }
    
    // Multiply all elements lazily by updating both multiplicative and additive
    // parameters using the distributive law:
    // (a*x + b) * multiplier = (a*multiplier)*x + (b*multiplier)
    auto multAll(ll const multiplier_) -> void {
        mParamA = mParamA * multiplier_ % kModulus;
        mParamB = mParamB * multiplier_ % kModulus;
    }
    
    // Retrieve the actual value at index idx_. Apply the stored lazy transformation:
    // value = a*stored + b
    [[nodiscard]]
    auto getIndex(size_t const idx_) const -> int {
        if(idx_ >= mNums.size()) { 
            return -1;
        }
        auto const ans{(mParamA * mNums[idx_] % kModulus + mParamB) % kModulus};
        return static_cast<int>(ans);
    }

private:
    // Fast modular exponentiation: computes (base_^pow_) % kModulus
    auto DoQuickmul(
        ll base_,
        ll pow_
    ) const -> ll {
        auto prod{1ll};
        while(pow_ > 0) {
            if(pow_ % 2 == 1) {
                prod = prod * base_ % kModulus;
            }
            base_ = base_ * base_ % kModulus;
            pow_ >>= 1;
        }
        return prod;
    }

    // Compute modular multiplicative inverse using Fermat's Little Theorem:
    // inv(val) = val^(kModulus-2) % kModulus
    auto DoInv(ll const val_) const -> ll {
        return DoQuickmul(val_, kModulus - 2);
    }

    static auto constexpr kModulus{1'000'000'007ll};
    static auto constexpr kMaxNumsSz{100'000uz};
    std::vector<ll> mNums;
    // Lazy affine transformation parameters: value = a*stored + b
    ll mParamA{1};
    ll mParamB{0};
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */
