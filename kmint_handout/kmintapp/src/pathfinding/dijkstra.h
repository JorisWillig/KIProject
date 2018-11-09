#pragma once
#include "pathfinder.h"
#include <map>
#include <queue>
#include <vector>
namespace pathfinding {

class Dijkstra : public IPathfinder {
public:
    Path findPath(map::map_graph& graph, map::map_node& start,
        map::map_node& target) override;

private:
    struct Comparator {
        Comparator(const Dijkstra& d)
            : dijkstra(d)
        {
        }

        bool operator()(map::map_node* lhs, map::map_node* rhs)
        {
            return dijkstra.getWeight(*lhs) < dijkstra.getWeight(*rhs);
        }
        const Dijkstra& dijkstra;
    };
    bool operator()(map::map_node* lhs, map::map_node* rhs)
    {
        return getWeight(*lhs) < getWeight(*rhs);
    };
    void buildPath(Path& path);
    bool hasCalculatedWeight(const map::map_node& node) const;
    float getWeight(const map::map_node& node) const;
    const map::map_node& getOtherNode(const map::map_edge& edge, const map::map_node& currentNode) const;
    std::map<const map::map_node*, float> m_weights;
    std::priority_queue<map::map_node*, std::vector<map::map_node*>, Comparator>
        m_nodeQueue{ Comparator(*this) };
};
} // namespace pathfinding