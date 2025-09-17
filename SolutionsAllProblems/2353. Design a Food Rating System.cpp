// problem : https://leetcode.com/problems/design-a-food-rating-system/description/
// submission : https://leetcode.com/problems/design-a-food-rating-system/submissions/1774239630
// solution post : https://leetcode.com/problems/design-a-food-rating-system/solutions/7200571/
//    c-modern-readable-code-optimal-time-comp-l7og

// import std;

// let 'n' be a count of the given food
// 'm' - number of calls to methods
// time complexity O((n + m) * log(n))
// space complexity O(1)
// runtime 134 ms, beats 67.04 %
class FoodRatings {
public:
    FoodRatings(
        std::vector<std::string> const & foods_,
        std::vector<std::string> const & cuisines_,
        std::vector<int> const & ratings_
    );
    auto changeRating(
        std::string const & food_,
        int const newRating_
    ) -> void;
    auto highestRated(std::string const & cuisine_) const -> std::string;

private:
    template<typename keyT_, typename valT_>
    using umT = std::unordered_map<keyT_, valT_>;
    template<typename val1T_, typename val2T_>
    using prT = std::pair<val1T_, val2T_>;
    using strT = std::string;

    static inline bool const kIsFastIO{
        [] () {
            std::ios_base::sync_with_stdio(false);
            std::cin.tie(nullptr);
            return true;
        } ()
    };
    umT<strT, int> mFoodToRating;
    umT<strT, strT> mCuisineToFood;
    umT<strT, std::set<prT<int, strT>>> mCuisineToFoodAndRating;
};

FoodRatings::FoodRatings(
    std::vector<std::string> const & foods_,
    std::vector<std::string> const & cuisines_,
    std::vector<int> const & ratings_
) {
    namespace views = std::views;
    auto const foodCnt{std::ssize(foods_)};
    for(auto const idx: views::iota(0, foodCnt)) {
        auto const & food{foods_.at(idx)};
        auto const & rating{ratings_.at(idx)};
        auto const & cuisine{cuisines_.at(idx)};
        mFoodToRating[food] = rating;
        mCuisineToFood[food] = cuisine;
        mCuisineToFoodAndRating[cuisine].emplace(-1 * rating, food);
    }
}

auto FoodRatings::changeRating(
    std::string const & food_,
    int const newRating_
) -> void {
    auto const & cuisine{mCuisineToFood.at(food_)};
    auto const rating{-1 * mFoodToRating.at(food_)};
    auto const oldRatingAndFoodIt{
        mCuisineToFoodAndRating.at(cuisine).find({rating, food_})};
    assert(
        oldRatingAndFoodIt != mCuisineToFoodAndRating.at(cuisine).cend());
    mCuisineToFoodAndRating.at(cuisine).erase(oldRatingAndFoodIt);
    mFoodToRating.at(food_) = newRating_;
    mCuisineToFoodAndRating.at(cuisine).emplace(-1 * newRating_, food_);
}

auto FoodRatings::highestRated(
    std::string const & cuisine_
) const -> std::string {
    auto const maxFood{
        mCuisineToFoodAndRating.at(cuisine_).begin()->second};
    return maxFood;
}
