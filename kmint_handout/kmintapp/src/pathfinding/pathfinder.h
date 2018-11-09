#pragma once

#include "path.h"
#include <kmint/map/map.hpp>

namespace pathfinding {
class IPathfinder {
public:
    virtual Path findPath(map::map_graph& graph, map::map_node& start,
        map::map_node& target)
        = 0;
};
} // namespace pathfinding