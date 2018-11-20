#include "cow.h"
#include "actors/hare.h"
#include "kmint/random.hpp"
#include "pathfinding/astar.h"
#include "pathfinding/dijkstra.h"
#include <iostream>

using namespace kmint;
namespace actors {
static const char* cow_image = "resources/cow.png";

Cow::Cow(map::map_graph& g, map::map_node const& initial_node)
    : play::map_bound_actor{ g, initial_node }
    , m_graph{ g }
    , drawable_{ *this,
        kmint::graphics::image{
            cow_image, 0.1 } }
    , m_currentPath{ &initial_node, &initial_node }
{
}

void Cow::act(delta_time dt)
{
    t_passed_ += dt;

    if (m_currentPath.route.empty()) {
        if (m_hare != nullptr) {
            pathfinding::Astar pathfinder{};
            m_currentPath = pathfinder.findPath(m_graph, &node(), &m_hare->node());
        }
    } else {
        if (to_seconds(t_passed_) >= 0.05) {
            auto nextNode = m_currentPath.route.front();
            // pick random edge
            for (size_t i = 0; i < node().num_edges(); i++) {
                auto otherNode = node()[i];
                if (otherNode.from().node_id() == nextNode->node_id()) {
                    this->node(otherNode.from());
                    break;
                } else if (otherNode.to().node_id() == nextNode->node_id()) {
                    this->node(otherNode.to());
                    break;
                }
            }
            t_passed_ = from_seconds(0);
            m_currentPath.route.pop();
        }
    }
}
} // namespace actors