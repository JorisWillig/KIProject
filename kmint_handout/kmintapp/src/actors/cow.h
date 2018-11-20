#pragma once

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "pathfinding/path.h"

namespace actors {

class Hare;

class Cow : public kmint::play::map_bound_actor {
public:
    Cow(kmint::map::map_graph& g, kmint::map::map_node const& initial_node);

    // wordt elke game tick aangeroepen
    void act(kmint::delta_time dt) override;

    kmint::ui::drawable const& drawable() const override { return drawable_; }

    // als incorporeal false is, doet de actor mee aan collision detection
    bool incorporeal() const override { return false; }

    // geeft de radius van deze actor mee. Belangrijk voor collision detection
    kmint::scalar radius() const override { return 16.0; }

    void setHare(const Hare* hare) { m_hare = hare; }

private:
    kmint::map::map_graph& m_graph;
    kmint::play::image_drawable drawable_;
    pathfinding::Path m_currentPath;
    const Hare* m_hare{};
    // hoeveel tijd is verstreken sinds de laatste beweging
    kmint::delta_time t_passed_{};
    // weet hoe de koe getekend moet worden

    // edge_type const *next_edge_{nullptr};
    // edge_type const *pick_next_edge();
};
} // namespace actors