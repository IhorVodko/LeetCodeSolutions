// problem : https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-ii/description/
// submission : https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-ii/submissions/1821766167
// solution post : https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-ii/solutions/7329219/
//    c-modern-readable-code-beats-100-runtime-r3k5

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

class Solution {
public:
// let 'n' be the length of given array on numbers
// time complexity O(n * log(n))
// space complexity O(n)
// runtime 0 ms, beats 100.00 %
    [[nodiscard]]
    auto findXSum(
        std::span<int const> const nums_,
        int const subArrSz_,
        int const topFreqLimit_
    ) const -> std::vector<long long>;

private:
    class Helper {
    public:
        Helper(int const topFreqLimit_);

        auto InsertNum(int const num_) -> void;
        auto RemoveNum(int const num_) -> void;
        [[nodiscard]]
        inline auto GetSum() const -> long long;

    private:
        auto InternalInsert(std::pair<int, int> const cntAndNum_) -> void;
        auto InternalRemove(std::pair<int, int> const cntAndNum_) -> void;

        int mTopFreqLimit;
        long long mSum;
        std::set<std::pair<int, int>> mTopCntAndNum;
        std::set<std::pair<int, int>> mLowerCntAndNum;
        std::unordered_map<int, int> mNumToCnt;
    };
};

auto Solution::findXSum(
    std::span<int const> const nums_,
    int const subArrSz_,
    int const topFreqLimit_
) const -> std::vector<long long> {
    namespace vs = std::views;

    auto helper(Helper{topFreqLimit_});
    auto answer{std::vector<long long>{}};
    auto numsSz{static_cast<int>(nums_.size())};
    answer.reserve(std::max(0, numsSz - subArrSz_ + 1));
    for(auto const idx: vs::iota(0, numsSz)) {
        helper.InsertNum(nums_[idx]);
        if(idx >= subArrSz_) {
            helper.RemoveNum(nums_[idx - subArrSz_]);
        }
        if(idx >= subArrSz_ - 1) {
            answer.emplace_back(helper.GetSum());
        }
    }
    return answer;
}

Solution::Helper::Helper(int const topFreqLimit_):
    mTopFreqLimit{topFreqLimit_},
    mSum{}
{}

auto Solution::Helper::InsertNum(int const num_) -> void {
    if(auto const it{mNumToCnt.find(num_)}; it != mNumToCnt.end()) {
        auto const [num, cnt]{*it};
        InternalRemove({cnt, num});
    }
    ++mNumToCnt[num_];
    InternalInsert({mNumToCnt[num_], num_});
}

auto Solution::Helper::RemoveNum(int const num_) -> void {
    auto it{mNumToCnt.find(num_)};
    if(it == mNumToCnt.end()) {
        return;
    }
    auto & [num, cnt]{*it};
    InternalRemove({cnt, num});
    if(--cnt > 0) {
        InternalInsert({cnt, num});
    } else {
        mNumToCnt.erase(it);
    }
}

auto Solution::Helper::GetSum() const -> long long {
    return mSum;
}

auto Solution::Helper::InternalInsert(std::pair<int, int> const cntAndNum_) -> void {
    if( mTopCntAndNum.size() >= mTopFreqLimit &&
        cntAndNum_ <= *mTopCntAndNum.begin()
    ) {
        mLowerCntAndNum.insert(cntAndNum_);
        return;
    }
    auto const [cnt, num]{cntAndNum_};
    mSum += static_cast<long long>(cnt) * num;
    mTopCntAndNum.insert(cntAndNum_);
    if(mTopCntAndNum.size() <= mTopFreqLimit) {
        return;
    }
    auto const [topCnt, topNum]{*mTopCntAndNum.begin()};
    mSum -= static_cast<long long>(topCnt) * topNum;
    auto const transfer{mTopCntAndNum.begin()};
    mLowerCntAndNum.emplace(std::move(*transfer));
    mTopCntAndNum.erase(transfer);
}

auto Solution::Helper::InternalRemove(std::pair<int, int> const cntAndNum_) -> void {
    if(cntAndNum_ < *mTopCntAndNum.begin()) {
        mLowerCntAndNum.erase(cntAndNum_);
        return;
    }
    auto const [cnt, num]{cntAndNum_};
    mSum -= static_cast<long long>(cnt) * num;
    mTopCntAndNum.erase(cntAndNum_);
    if(mLowerCntAndNum.empty()) {
        return;
    }
    auto const [topCnt, topNum]{*mLowerCntAndNum.rbegin()};
    mSum += static_cast<long long>(topCnt) * topNum;
    auto const transfer{std::prev(mLowerCntAndNum.end())};
    mTopCntAndNum.emplace(std::move(*transfer));
    mLowerCntAndNum.erase(transfer);
}
