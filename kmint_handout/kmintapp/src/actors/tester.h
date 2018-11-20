#pragma once
#include "drawables/rectangle.h"
#include "kmint/graphics.hpp" // kleuren en afbeeldingen
#include "kmint/map/map.hpp"
#include "kmint/math/vector2d.hpp" // voor window en app
#include "kmint/play.hpp"          // voor stage
#include "kmint/ui.hpp"            // voor window en app
using namespace kmint;
namespace actors {

class Tester : public play::free_roaming_actor {
public:
  Tester(math::vector2d location)
      : free_roaming_actor{location}, drawable_{*this} {}

  void move(math::vector2d delta) { location(location() + delta); }

  const ui::drawable &drawable() const override { return drawable_; }

private:
  drawables::RectangleDrawable drawable_;
};
} // namespace actors