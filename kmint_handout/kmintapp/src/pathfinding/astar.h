#pragma once
#include "pathfinder.h"
#include <cmath>
#include <map>
#include <queue>
#include <vector>
namespace pathfinding {

class Astar : public IPathfinder {
public:
    Path findPath(map::map_graph& graph, const map::map_node* start,
        const map::map_node* target) override;

private:
    struct Comparator {
        Comparator(const Astar& d)
            : astar(d)
        {
        }

        bool operator()(const map::map_node* lhs, const map::map_node* rhs)
        {
            return getCompareValue(lhs) < getCompareValue(rhs);
        }

        float getCompareValue(const map::map_node* node)
        {
            if (astar.hasCalculatedWeight(*node)) {
                return getHeuristic(node) + astar.getWeight(*node);
            } else {
                return astar.getWeight(*node);
            }
        }

        float getHeuristic(const map::map_node* node)
        {
            float xDifference = std::abs(node->location().x() - astar.m_target->location().x());
            float yDifference = std::abs(node->location().y() - astar.m_target->location().y());
            return xDifference + yDifference;
        }
        const Astar& astar;
    };
    void buildPath(Path& path);
    bool hasCalculatedWeight(const map::map_node& node) const;
    float getWeight(const map::map_node& node) const;
    const map::map_node& getOtherNode(const map::map_edge& edge, const map::map_node& currentNode) const;
    std::map<const map::map_node*, float> m_weights;
    std::priority_queue<const map::map_node*, std::vector<const map::map_node*>, Comparator>
        m_nodeQueue{ Comparator(*this) };
    map::map_graph* m_graph;
    const map::map_node* m_target;
};
} // namespace pathfinding