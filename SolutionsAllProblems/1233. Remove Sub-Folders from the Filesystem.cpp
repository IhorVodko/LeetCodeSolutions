// problem : https://leetcode.com/problems/remove-sub-folders-from-the-filesystem/description
// submission : https://leetcode.com/problems/remove-sub-folders-from-the-filesystem/submissions/1706166301
// solution post : https://leetcode.com/problems/remove-sub-folders-from-the-filesystem/solutions/6986767
//    /c-modern-readable-code-optimal-time-comp-9i2r

// #include <istream>
// #include <string>
// #include <vector>

namespace Util {

using PathT = std::string;
using FolderT = std::string;
using PathesT = std::vector<PathT>;

inline auto constexpr kPathDelim{'/'};

struct TrieNode {
    using FolderT = Util::FolderT; 
    bool mIsEndOfPath{false};
    std::unordered_map<FolderT, std::shared_ptr<TrieNode>> mSubfolders;
};

}

class Solution {
public:
    using PathesT = Util::PathesT;
    using TrieNode = Util::TrieNode;
// let 'p' be a count of the given pathes
// 'l' - average length of a path
// time complexity O(p * l)
// space complexity O(p * l)
// runtime 267 ms, beats 5.71 %
    [[nodiscard]] 
    PathesT removeSubfolders(PathesT const & pathes_) const;
private:
    void ConvertPathesToTrie(PathesT const & pathes_) const;
    Solution::PathesT FindOnlyParentPathes(PathesT const & pathes_) const;
    std::shared_ptr<TrieNode> mRootFolder{std::make_shared<TrieNode>()};
};

Solution::PathesT Solution::removeSubfolders(PathesT const & pathes_) const {
    using namespace Util;
    ConvertPathesToTrie(pathes_);
    auto const parentPathes{FindOnlyParentPathes(pathes_)};
    return parentPathes;
}

void Solution::ConvertPathesToTrie(PathesT const & pathes_) const {
    using namespace Util;
    for(auto const & path: pathes_) {
        auto currFolder{mRootFolder}; 
        auto pathStream{std::istringstream{path}};
        auto validatedFolder{FolderT{}};
        while(std::getline(pathStream, validatedFolder, kPathDelim)) {
            if(validatedFolder.empty()) {
                continue;
            }
            if(!currFolder->mSubfolders.contains(validatedFolder)) {
                currFolder->mSubfolders[validatedFolder] = make_shared<TrieNode>();
            }
            currFolder = currFolder->mSubfolders.at(validatedFolder);
        }
        currFolder->mIsEndOfPath = true;
    }
}

Solution::PathesT Solution::FindOnlyParentPathes(PathesT const & pathes_) const {
    using namespace Util;
    auto parentPathes{PathesT{}};
    for(auto const & path: pathes_) {
        auto currFolder{mRootFolder};
        auto pathStream{std::istringstream{path}};
        auto validatedFolder{FolderT{}};
        auto isSubfolder{false};
        while(std::getline(pathStream, validatedFolder, '/')) {
            if(validatedFolder.empty()) {
                continue;
            }
            auto const nextFolder{currFolder->mSubfolders.at(validatedFolder)};
            if(     nextFolder->mIsEndOfPath
                &&  pathStream.rdbuf()->in_avail() != 0
            ) {
                isSubfolder = true;
                break;
            }
            currFolder = nextFolder;
        }
        if(!isSubfolder) {
            parentPathes.emplace_back(path);
        }
    }
    return parentPathes;
}
