// problem : https://leetcode.com/problems/duplicate-zeros/description/
// submission : https://leetcode.com/problems/duplicate-zeros/submissions/1463649379
// solution post: https://leetcode.com/problems/duplicate-zeros/solutions/6086705/c-modern-readable-code-beats-100-runtime

// #include <cassert>
// #include <vector>


class Solution{
public:
    // let 'n' be an input length
    // time complexity O(n)
    // space complexity O(1)
    // runtime 0 ms, beats 100.00 %
    // memory 13.79 mb, beats 6.22 %
    void duplicateZeros(std::vector<int> & arr) {
        if(arr.size() == 1){
            return;
        }
        auto delta{int(1)};
        auto lastIndx{int(arr.size() - 1)};
        for(auto indx{int(0)}; indx <= lastIndx; ++indx){
            if(arr.at(indx) == 0){
                if(indx == lastIndx){
                    arr.back() = arr.at(indx);
                    ++delta;
                    --lastIndx;
                    break;
                }
                --lastIndx;
            }
        }
        for(auto indx{int(arr.size() - delta)}; indx >= 0 && lastIndx >= 0;
            --indx, --lastIndx
        ){
            arr.at(indx) = arr.at(lastIndx);
            if(arr.at(lastIndx) == 0){
                --indx;
                assert((indx >= 0) && "Oops!");
                arr.at(indx) = 0;
            }
        }
    }
};
