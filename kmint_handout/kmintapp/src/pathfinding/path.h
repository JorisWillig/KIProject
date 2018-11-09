#pragma once
#include <kmint/main.hpp>
#include <kmint/map/map.hpp>
#include <vector>
using namespace kmint;
namespace pathfinding {
struct Path {
    map::map_node& target;
    map::map_node& origin;
    std::vector<map::map_node*> route{};
    Path(map::map_node& origin, map::map_node& target)
        : target{ target }
        , origin{ origin }
    {
    }
};
} // namespace pathfinding