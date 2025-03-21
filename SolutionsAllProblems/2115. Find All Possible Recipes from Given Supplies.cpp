// problem : https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies/description/
// submission : https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies/submissions/1581436239
// solution post : https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies/solutions/6563559/
//     c-modern-readable-code-beats-96-runtime-zu0yy

// #include <vector>
// #include <string>
// #include <string_view>
// #include <unordered_set>
// #include <unordered_map>

// let 'r' be a count of recipes
// 'i' - count of ingredients across all recipes
// 's' - count of supplies
// time complexity O(r + i + s)
// space complexity O(r + i + s)
// runtime 30 ms, beats 96.04 %
class Solution {
public:
    template<typename T_>
    using Arr1T = std::vector<T_>;
    template<typename T_>
    using Arr2T = std::vector<Arr1T<T_>>;

    Arr1T<std::string> findAllRecipes(
        Arr1T<std::string> const & recipes_,
        Arr2T<std::string> const & ingredients_,
        Arr1T<std::string> const & supplies_
    ) const {
        auto suppliesSet{std::unordered_set<std::string_view>{
            supplies_.cbegin(), supplies_.cend()}};
        auto recipeToIdx{std::unordered_map<std::string_view, int>{}};
        auto ingredientToItsDependents{std::unordered_map<std::string,
            Arr1T<std::string_view>>{}};
        for(auto idx{0}; idx < recipes_.size(); ++idx) {
            recipeToIdx[recipes_.at(idx)] = idx;
        }    
        auto unavailableIndgredientsCount{std::vector<int>(
            recipes_.size(), 0)}; 
        for(auto recipeIdx{0}; recipeIdx < recipes_.size(); ++recipeIdx) {
            for(auto const ingredient: ingredients_.at(recipeIdx)) {
                if(!suppliesSet.contains(ingredient)) {
                    ingredientToItsDependents[ingredient].emplace_back(
                        recipes_.at(recipeIdx));    
                    ++unavailableIndgredientsCount.at(recipeIdx);
                } 
            } 
        }
        auto queueRecepyIdxs{std::queue<int>{}};
        for(auto recipeIdx{0}; recipeIdx < recipes_.size(); ++recipeIdx) {
            if(unavailableIndgredientsCount[recipeIdx] == 0) {
                queueRecepyIdxs.emplace(recipeIdx);
            }
        }
        auto producableRecipes{Arr1T<std::string>{}};
        while(!queueRecepyIdxs.empty()) {
            auto const & recipe{recipes_.at(queueRecepyIdxs.front())};
            queueRecepyIdxs.pop();
            producableRecipes.emplace_back(recipe);
            if(!ingredientToItsDependents.contains(recipe)) {
                continue;
            }
            for(auto const dependentRecipe:
                ingredientToItsDependents.at(recipe)
            ) {
                if(--unavailableIndgredientsCount.at(recipeToIdx.at(
                        dependentRecipe)) == 0
                ) {
                    queueRecepyIdxs.emplace(recipeToIdx.at(dependentRecipe));
                }
            }
        }
        return producableRecipes;
    }
};
