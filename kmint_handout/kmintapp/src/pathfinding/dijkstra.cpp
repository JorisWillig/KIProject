#include "dijkstra.h"
#include <iostream>
#include <limits>
#include <stack>
#include <vector>

namespace pathfinding {
Path Dijkstra::findPath(map::map_graph& graph, const map::map_node* start,
    const map::map_node* target)
{
    m_graph = &graph;
    Path path{ start, target };
    // fill the queue with all the nodes
    m_weights[start] = 0;
    m_nodeQueue.push(start);
    graph.untag_all();
    buildPath(path);
    //TODO: cleanup class for a next request
    m_weights.clear();
    return path;
}

float Dijkstra::getWeight(const map::map_node& node) const
{
    auto it = m_weights.find(&node);
    if (it != m_weights.end()) {
        return it->second;
    } else {
        return std::numeric_limits<float>::max();
    }
}

void Dijkstra::buildPath(Path& path)
{
    std::map<const map::map_node*, const map::map_node*> previousNodes{};
    while (!m_nodeQueue.empty()) {
        auto* node = m_nodeQueue.top();
        if (node != path.target && hasCalculatedWeight(*node)) {
            for (size_t i = 0; i < node->num_edges(); i++) {
                const map::map_edge& edge = (*node)[i];
                const auto& nextNode = getOtherNode(edge, *node);

                float weight = edge.weight() + getWeight(*node);
                if (weight < getWeight(nextNode) && weight < getWeight(*path.target)) {
                    (*m_graph)[nextNode.node_id()].tagged(true);
                    m_weights[&nextNode] = weight;
                    previousNodes[&nextNode] = node;
                    m_nodeQueue.push(&nextNode);
                }
            }
        }

        m_nodeQueue.pop();
    }
    // backtrack to find path
    const map::map_node* currentNode = path.target;
    std::stack<const map::map_node*> reversedRoute{};
    while (previousNodes.find(currentNode) != previousNodes.end()) {
        reversedRoute.push(currentNode);
        currentNode = previousNodes[currentNode];
    }
    // reverse the route and insert into path's route
    while (!reversedRoute.empty()) {
        auto* node = reversedRoute.top();
        path.route.push(node);
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