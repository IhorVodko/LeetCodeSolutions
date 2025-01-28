// problem : https://leetcode.com/problems/course-schedule-iv/description/
// submission : https://leetcode.com/problems/course-schedule-iv/submissions/1523464186
// solution post : https://leetcode.com/problems/course-schedule-iv/solutions/6340766/c-modern-readable-code-optimal-time-comp-n8jv

// #include <vector>

// let 'n' be a parameter 'numCourses' value
// 'q' - 'queries' length
// time complexity O(n^3 + q)
// space complexity O(n^2)
// runtime 251 ms, beats 16.26 %
class Solution {
public:
    template<typename T>
    using Mx = std::vector<std::vector<T>>;
    std::vector<bool> checkIfPrerequisite(
        int const numCourses,
        Mx<int> const & prerequisites,
        Mx<int> const & queries
    ) const {
        if(prerequisites.empty()) {
            return std::vector<bool>(queries.size(), false);
        } 
        auto isPrerequisitesMx{Mx<bool>(numCourses,
            std::vector<bool>(numCourses, false))};
        for(auto const & prerequisite: prerequisites) {
            isPrerequisitesMx.at(prerequisite.at(0)).at(prerequisite.at(1)) =
                true;
        }
        for(auto intermidiateCourse{size_t{0}}; intermidiateCourse < numCourses;
            ++intermidiateCourse
        ) {
            for(auto sourceCourse{size_t{0}}; sourceCourse < numCourses;
                ++sourceCourse
            ) {
                for(auto targetCourse{size_t{0}}; targetCourse < numCourses;
                    ++targetCourse
                ) {
                    if(isPrerequisitesMx.at(sourceCourse).at(targetCourse)) {
                        continue;
                    }
                    isPrerequisitesMx.at(sourceCourse).at(targetCourse) =
                        isPrerequisitesMx.at(sourceCourse).
                            at(intermidiateCourse) &&
                        isPrerequisitesMx.at(intermidiateCourse).
                                at(targetCourse);
                }
            }
        }
        auto isPrerequisites{std::vector<bool>{}};
        isPrerequisites.reserve(queries.size());
        for(auto const & querie: queries) {
            isPrerequisites.emplace_back(isPrerequisitesMx.at(querie.at(0)).
                at(querie.at(1)));
        }
        return isPrerequisites;
    }
};
