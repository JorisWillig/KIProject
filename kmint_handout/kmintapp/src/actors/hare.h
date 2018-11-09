#pragma once
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "kmint/random.hpp"

class Cow;

class Hare : public kmint::play::map_bound_actor {
public:
  Hare(kmint::map::map_graph const &g);
  void act(kmint::delta_time dt) override;
  kmint::ui::drawable const &drawable() const override { return drawable_; }
  void set_cow(Cow const &c) { cow_ = &c; }
  bool incorporeal() const override { return false; }
  kmint::scalar radius() const override { return 16.0; }

private:
  kmint::play::image_drawable drawable_;
  Cow const *cow_;
};