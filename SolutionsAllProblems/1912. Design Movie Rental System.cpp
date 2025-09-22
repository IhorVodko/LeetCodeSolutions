// problem : https://leetcode.com/problems/design-movie-rental-system/description/
// submission : https://leetcode.com/problems/design-movie-rental-system/submissions/1779114197
// solution post : https://leetcode.com/problems/design-movie-rental-system/solutions/7214000/
//    c-modern-readable-code-beats-99-runtime-htett

// import std;

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */

class Entry {
public:
    Entry(
       int const shop_ = 0,
       int const movie_ = 0,
       int const price_ = 0 
    ):
        mShop{shop_},
        mMovie{movie_},
        mPrice{price_}
    {
        assert(shop_ >= 0 && movie_ >= 0 && price_ >= 0);
    }
    Entry(std::vector<int> const & entry_):
        Entry{entry_.at(0), entry_.at(1), entry_.at(2)}
    {}

    auto shop() const noexcept -> int {
        return mShop;
    }
    auto movie() const noexcept -> int {
        return mMovie;
    }
    auto price() const noexcept -> int {
        return mPrice;
    }

private:
    int mShop;
    int mMovie;
    int mPrice;
};

// let 's' be a shops count given
// 'c' - number of calls to the class
// time complexity O(s + c * log(s))
// space complexity O(s)
// runtime 186 ms, beats 99.31 %
class MovieRentingSystem {
public:
    // time complexity O(s)
    // space complexity O(s)
    MovieRentingSystem(
        int shopSz_ = 0, 
        std::vector<std::vector<int>> const & entries_ = {}
    );
    // time complexity O(1)
    // space complexity O(s)
    auto search(int const movie_) const -> std::vector<int>;
    // time complexity O(log(s))
    // space complexity O(s)
    auto rent(
        int const shop_,
        int const movie_
    ) -> void;
    // time complexity O(log(s))
    // space complexity O(s)
    auto drop(
        int const shop_,
        int const movie_
    ) -> void;
    // time complexity O(1)
    // space complexity O(s)
    auto report() const -> std::vector<std::vector<int>>;

private:
    struct ShopMovieHash {
        auto operator()(
            std::pair<int, int> const & shopMovie_
        ) const -> size_t;
    };

    inline static bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
    inline static int constexpr kContainerSzLimit{5};
    int mShopSz;
    std::unordered_map<std::pair<int, int>, int, ShopMovieHash>
        mUMapShopAndMovieToPrice;
    std::unordered_map<int, std::set<std::pair<int, int>>>
        mUMapMovieToSetPriceAndShop;
    std::unordered_set<std::pair<int, int>, ShopMovieHash>
        mRentedUSetShopAndMovie;
    std::set<std::array<int, 3>> mRentedSetPriceAndShopAndMovie;
};

MovieRentingSystem::MovieRentingSystem(
    int shopSz_, 
    std::vector<std::vector<int>> const & entries_
):
    mShopSz{shopSz_}
{
    assert(shopSz_ >= 0);
    auto const entriesSz{std::ssize(entries_)};
    mUMapShopAndMovieToPrice.reserve(entriesSz);
    mUMapMovieToSetPriceAndShop.reserve(entriesSz);
    mRentedUSetShopAndMovie.reserve(entriesSz);
    for(auto const & entry: entries_) {
        auto const shop{entry.at(0)};
        auto const movie{entry.at(1)};
        auto const price{entry.at(2)};
        assert(shop >= 0 && movie >= 0 && price >= 0);
        assert(!mUMapShopAndMovieToPrice.contains({shop, movie}));
        mUMapShopAndMovieToPrice[{shop, movie}] = price;
        assert(!mUMapMovieToSetPriceAndShop[movie].
            contains({price, shop}));
        mUMapMovieToSetPriceAndShop[movie].emplace(price, shop);
    }
}

auto MovieRentingSystem::search(int const movie_) const -> std::vector<int> {
    if(!mUMapMovieToSetPriceAndShop.contains(movie_)) {
        return {};
    }
    auto cheapestShops{std::vector<int>{}}; 
    cheapestShops.reserve(kContainerSzLimit);
    auto const & priceShop{mUMapMovieToSetPriceAndShop.at(movie_)};
    for(auto const [_, shop]: priceShop) {
        if(mRentedUSetShopAndMovie.contains({shop, movie_})) {
            continue;
        }
        if(cheapestShops.size() >= kContainerSzLimit) {
            break;
        } 
        cheapestShops.emplace_back(shop);
    }
    return cheapestShops;
}

auto MovieRentingSystem::rent(
    int const shop_,
    int const movie_
) -> void {
    assert(mRentedUSetShopAndMovie.size() ==
        mRentedSetPriceAndShopAndMovie.size());
    assert(!mRentedUSetShopAndMovie.contains({shop_, movie_}));
    mRentedUSetShopAndMovie.emplace(shop_, movie_);
    auto const price{mUMapShopAndMovieToPrice.at({shop_, movie_})};
    assert(!mRentedSetPriceAndShopAndMovie.contains(
        std::to_array({price, shop_, movie_})));
    mRentedSetPriceAndShopAndMovie.emplace(
        std::to_array({price, shop_, movie_}));
}

auto MovieRentingSystem::drop(
    int const shop_,
    int const movie_
) -> void {
    assert(mRentedUSetShopAndMovie.size() ==
        mRentedSetPriceAndShopAndMovie.size());
    assert(mRentedUSetShopAndMovie.contains({shop_, movie_}));
    mRentedUSetShopAndMovie.erase({shop_, movie_});
    auto const price{mUMapShopAndMovieToPrice.at({shop_, movie_})};
    assert(mRentedSetPriceAndShopAndMovie.contains(
        std::to_array({price, shop_, movie_})));
    mRentedSetPriceAndShopAndMovie.erase(
        std::to_array({price, shop_, movie_}));
}

auto MovieRentingSystem::report() const -> std::vector<std::vector<int>> {
    assert(mRentedUSetShopAndMovie.size() ==
        mRentedSetPriceAndShopAndMovie.size());
    if(mRentedSetPriceAndShopAndMovie.empty()) {
        return {};
    }
    auto cheapestRented{std::vector<std::vector<int>>{}};
    cheapestRented.reserve(kContainerSzLimit);
    for(auto const [_, shop, movie]: mRentedSetPriceAndShopAndMovie) {
        if(cheapestRented.size() >= kContainerSzLimit) {
            break;
        }
        cheapestRented.emplace_back(
            std::initializer_list{shop, movie});
    } 
    return cheapestRented;  
}

auto MovieRentingSystem::ShopMovieHash::operator()(
        std::pair<int, int> const & shopMovie_
    ) const -> size_t {
    auto const hash1{std::hash<int>{}(shopMovie_.first)};
    auto const hash2{std::hash<int>{}(shopMovie_.second)};
    auto const hashFinal{
        hash1 ^
        (   hash2 +
            0x9e3779b9 +
            (hash1 << 6) +
            (hash1 >> 2)    )
    };
    return hashFinal;
}
