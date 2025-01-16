// problem : https://leetcode.com/problems/unique-word-abbreviation/description/
// submission : https://leetcode.com/problems/unique-word-abbreviation/submissions/1510841832
// solution post : https://leetcode.com/problems/unique-word-abbreviation/solutions/6291159/c-modern-readable-code-optimal-time-comp-tdqs

// #include <string>
// #include <vector>
// #include <unordered_map>
// #include <unordered_set>

// let 'n' be a parameter 'dictionary' length
// time complexity O(n)
// space complexity O(n)
// runtime 42 ms, beats 85.51 %
class ValidWordAbbr {
public:
    using WordsT = std::vector<std::string>;
    ValidWordAbbr(WordsT & dictionary) {
        Init(dictionary);
    }
    bool isUnique(std::string const & word) const {
        auto const abr{DoAbr(word)};
        if(!abrsToIsManyWords.contains(abr) || 
            (!abrsToIsManyWords.at(abr) && dictWords.contains(word))
        ) {
            return true;
        } 
        return false;
    }
private:
    void Init(WordsT & dictionary) {
        for(auto & word: dictionary) {
            auto abr{DoAbr(word)};
            abrsToIsManyWords[std::move(abr)] =
                abrsToIsManyWords.contains(abr) && 
                !dictWords.contains(word);
            dictWords.emplace(std::move(word));
        }

    }
    std::string DoAbr(std::string const & str) const {
        return str.size() <= 2 ? str :
            *str.begin() + std::to_string(str.size() - 2) + *str.rbegin();
    }
    std::unordered_map<std::string, bool> abrsToIsManyWords;
    std::unordered_set<std::string> dictWords;
};

/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr* obj = new ValidWordAbbr(dictionary);
 * bool param_1 = obj->isUnique(word);
 */
