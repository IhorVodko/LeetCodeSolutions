// problem : https://leetcode.com/problems/remove-methods-from-project/description
// submission : https://leetcode.com/problems/remove-methods-from-project/submissions/2095850683
// solution post : https://leetcode.com/problems/remove-methods-from-project/solutions/8443546/
//    simplanation-simple-explanation-by-cyber-rnyu

// Approach : Reachability Analysis via Depth First Search (DFS) with Indegree Subtraction
// Runtime : 19 ms, beats 99.66 %

// Complexity analysis
// let 'V' be the number of methods (nodes)
// 'E' - number of invocations (edges)
// Time :  O(V + E)
// Space : O(V + E)

// import std;

namespace {

namespace rs = std::ranges;
namespace vs = std::views;

// Adjacency list edge for forward star graph representation
struct InvocationEdge {
    int targetMethod{};
    int nextEdgeIdx{-1};
};

// Initializer to configure fast I/O before main() runs
auto const fastIOInit{
    [] {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        return 0;
    } ()
};

} // namespace 

class Solution final {
public:
    [[nodiscard]]
    static auto remainingMethods(
        int const totMethods_, 
        int const buggyMethod_, 
        std::vector<std::vector<int>> const & invocations_
    ) -> std::vector<int>;
};

auto Solution::remainingMethods(
    int const totMethods_, 
    int const buggyMethod_, 
    std::vector<std::vector<int>> const & invocations_
) -> std::vector<int> {
    // Linked list heads for each method's outgoing edges
    auto methodHeads{std::vector(totMethods_, -1)};
    auto methodIndegrees{std::vector(totMethods_, 0)};

    auto edgePool{std::vector<InvocationEdge>{}};
    edgePool.reserve(totMethods_);

    for(auto const & inv: invocations_) {
        auto const caller{inv[0]};
        auto const callee{inv[1]};

        // Build forward star graph representation
        edgePool.emplace_back(callee, methodHeads[caller]);
        methodHeads[caller] = static_cast<int>(edgePool.size()) - 1; 

        ++methodIndegrees[callee];
    }

    auto isBuggyMethods{std::vector<std::uint8_t>(totMethods_)};
    auto traversalStck{std::vector<int>{}};

    traversalStck.emplace_back(buggyMethod_);
    isBuggyMethods[buggyMethod_] = 1;

    // DFS traverse all reachable methods originating from the buggy one
    while(!traversalStck.empty()) {
        auto const caller{traversalStck.back()};
        traversalStck.pop_back();

        for(auto edgeIdx{methodHeads[caller]};
            edgeIdx != -1;
            edgeIdx = edgePool[edgeIdx].nextEdgeIdx
        ) {
            auto const callee{edgePool[edgeIdx].targetMethod};

            // Remove internal dependencies within the buggy component
            --methodIndegrees[callee];

            if(isBuggyMethods[callee] == 1) {
                continue;
            }
            
            isBuggyMethods[callee] = 1;
            traversalStck.emplace_back(callee);
        }
    }

    auto allMethods{vs::iota(0, totMethods_)};

    // Component cannot be isolated if it has unresolved external incoming edges
    auto const isIsolationFailed{rs::any_of(
        allMethods,
        [&] (auto const method_) {
            return isBuggyMethods[method_] == 1 && methodIndegrees[method_] > 0;
        }
    )};

    if(isIsolationFailed) {
        return rs::to<std::vector>(allMethods);
    }

    auto nonBuggyMethods{
        allMethods |
        vs::filter([&] (auto const method_) { return isBuggyMethods[method_] == 0; })
    };

    return rs::to<std::vector>(nonBuggyMethods);
}
