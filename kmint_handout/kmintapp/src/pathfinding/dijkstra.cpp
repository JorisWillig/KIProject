#include "dijkstra.h"
#include <limits>
#include <stack>
#include <vector>

namespace pathfinding {
Path Dijkstra::findPath(map::map_graph& graph, map::map_node& start,
    map::map_node& target)
{
    Path path{ start, target };
    // fill the queue with all the nodes
    for (size_t i = 0; i < graph.num_nodes(); i++) {
        auto& node = graph[i];
        m_nodeQueue.push(&node);
    }
    buildPath(path);
    //TODO: cleanup class for a next request
    return path;
}

float Dijkstra::getWeight(const map::map_node& node) const
{
    auto it = m_weights.find(&node);
    if (it != m_weights.end()) {
        return it->second;
    } else {
        return std::numeric_limits<int>::max();
    }
}

void Dijkstra::buildPath(Path& path)
{
    std::map<const map::map_node*, map::map_node*> previousNodes{};
    if (!m_nodeQueue.empty()) {
        auto* node = m_nodeQueue.top();
        if (node != &path.target && hasCalculatedWeight(*node)) {
            for (size_t i = 0; i < node->num_edges(); i++) {
                const map::map_edge& edge = (*node)[i];
                const auto& otherNode = getOtherNode(edge, *node);
                float weight = edge.weight() + getWeight(*node);
                if (weight < getWeight(otherNode) && weight < getWeight(path.target)) {
                    m_weights[&otherNode] = weight;
                    otherNode.tagged();
                    previousNodes[&otherNode] = node;
                }
            }
        }

        m_nodeQueue.pop();
    }
    // backtrack to find path
    map::map_node* currentNode = &path.target;
    std::stack<map::map_node*> reversedRoute{};
    while (previousNodes.find(currentNode) != previousNodes.end()) {
        reversedRoute.push(currentNode);
        currentNode = previousNodes[currentNode];
    }
    // reverse the route and insert into path's route
    while (!reversedRoute.empty()) {
        auto* node = reversedRoute.top();
        path.route.push_back(node);
        reversedRoute.pop();
    }
}

bool Dijkstra::hasCalculatedWeight(const map::map_node& node) const
{
    return m_weights.find(&node) != m_weights.cend();
}

const map::map_node& Dijkstra::getOtherNode(const map::map_edge& edge, const map::map_node& currentNode) const
{
    if (&currentNode == &edge.from()) {
        return edge.to();
    } else {
        return edge.from();
    }
}
} // namespace pathfinding