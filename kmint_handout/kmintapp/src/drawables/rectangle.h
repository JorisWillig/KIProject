#pragma once
#include <kmint/play.hpp>
#include <kmint/ui.hpp>
using namespace kmint;
namespace drawables {
class RectangleDrawable : public ui::drawable {
public:
  RectangleDrawable(play::actor const &actor) : drawable{}, actor_{&actor} {}

  void draw(ui::frame &f) const override {
    f.draw_rectangle(actor_->location(), {10.0, 10.0}, graphics::colors::white);
  };

private:
  play::actor const *actor_;
};
} // namespace drawables