// problem : https://leetcode.com/problems/delete-duplicate-folders-in-system/description/
// submission : https://leetcode.com/problems/delete-duplicate-folders-in-system/submissions/1707478679
// solution post : https://leetcode.com/problems/delete-duplicate-folders-in-system/solutions/6991523
//    /c-modern-readable-code-optimal-time-comp-tgjz

// #include <algorithm>
// #include <string>
// #include <vector>
// #include <unordered_map>

namespace Util {

using FolderT = std::string;
using FolderSerialT = std::string;
using PathT = std::vector<FolderT>;
using PathsT = std::vector<PathT>;

struct TrieNode {
    using FolderSerialT = Util::FolderSerialT;
    FolderSerialT mSerialPath;
    std::unordered_map<FolderSerialT, std::shared_ptr<TrieNode>> mFolderToSubs;
};

}

class Solution {
public:
    using PathsT = Util::PathsT;
    using TrieNode = Util::TrieNode;
    using FolderSerialT = Util::FolderSerialT;
// let 'f' be a count of folders given
// 's' - average serialized folder path
// time complexity O(f * s + f * log2(f))
// space complexity O(f * s)
// runtime 212 ms, beats 41.62 %
    [[nodiscard]]
    PathsT deleteDuplicateFolder(PathsT const & paths_) const;
private:
    [[nodiscard]]
    std::shared_ptr<TrieNode> BuildFoldersTree(PathsT const & paths_) const;
    void BuildSerialFoldersTree(
        std::unordered_map<FolderSerialT, size_t> & folderSerialToCount_,
        std::shared_ptr<TrieNode> const & node_
    ) const;
    void ReuseOnlyUniquePaths(
        Util::PathsT & uniquePaths,
        Util::PathT & path_,
        std::unordered_map<FolderSerialT, size_t> & folderSerialToCount_,
        std::shared_ptr<TrieNode> const & node_
    ) const;
};

Solution::PathsT Solution::deleteDuplicateFolder(PathsT const & paths_) const {
    namespace ranges = std::ranges;
    using namespace Util;
    auto const rootNode{BuildFoldersTree(paths_)};
    auto folderSerialToCount{std::unordered_map<FolderSerialT, size_t>{}};
    BuildSerialFoldersTree(folderSerialToCount, rootNode);
    auto uniquePaths{PathsT{}};
    auto path{PathT{}};
    ReuseOnlyUniquePaths(
        uniquePaths,
        path,
        folderSerialToCount,
        rootNode);
    return uniquePaths;
}

std::shared_ptr<Util::TrieNode> Solution::BuildFoldersTree(
    PathsT const & paths_
) const {
    auto const rootNode{std::make_shared<TrieNode>()};
    for(auto const & path: paths_) {
        auto currNode{rootNode};
        for(auto const & folder: path) {
            auto & folderToSubs{currNode->mFolderToSubs};
            if(!folderToSubs.contains(folder)) {
                folderToSubs[folder] = std::make_shared<TrieNode>();
            }
            currNode = folderToSubs.at(folder);
        }
    }
    return rootNode;
}


void Solution::BuildSerialFoldersTree(
    std::unordered_map<Util::FolderSerialT, size_t> & folderSerialToCount_,
    std::shared_ptr<TrieNode> const & node_
) const {
    using namespace Util;
    if(node_->mFolderToSubs.empty()) {
        return;
    }    
    auto path{PathT{}};
    for(auto const & [folder, subs]: node_->mFolderToSubs) {
        BuildSerialFoldersTree(folderSerialToCount_, subs);
        path.emplace_back(folder + "(" + subs->mSerialPath + ")");
    } 
    ranges::sort(path);
    for(auto & folder: path) {
        node_->mSerialPath += std::move(folder);
    }
    ++folderSerialToCount_[node_->mSerialPath];
}

void Solution::ReuseOnlyUniquePaths(
    Util::PathsT & uniquePaths_,
    Util::PathT & path_,
    std::unordered_map<FolderSerialT, size_t> & folderSerialToCount_,
    std::shared_ptr<TrieNode> const & node_
) const {
    if(folderSerialToCount_[node_->mSerialPath] > 1) {
        return;
    }
    if(!path_.empty()) {
        uniquePaths_.emplace_back(path_);
    }
    for(auto const & [folder, subs]: node_->mFolderToSubs) {
        path_.emplace_back(folder);
        ReuseOnlyUniquePaths(
            uniquePaths_,
            path_,
            folderSerialToCount_,
            subs);        
        path_.pop_back();
    }
}
