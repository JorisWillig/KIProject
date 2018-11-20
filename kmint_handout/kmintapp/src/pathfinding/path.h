#pragma once
#include <kmint/main.hpp>
#include <kmint/map/map.hpp>
#include <queue>
using namespace kmint;
namespace pathfinding {
struct Path {
    const map::map_node* target;
    const map::map_node* origin;
    std::queue<const map::map_node*> route{};
    Path(const map::map_node* origin, const map::map_node* target)
        : target{ target }
        , origin{ origin }
    {
    }
};
} // namespace pathfinding