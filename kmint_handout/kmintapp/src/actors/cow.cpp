#include "cow.h"
#include "kmint/random.hpp"
using namespace kmint;

static const char *cow_image = "resources/cow.png";
Cow::Cow(map::map_graph const &g, map::map_node const &initial_node)
    : play::map_bound_actor{g, initial_node}, drawable_{*this,
                                                        kmint::graphics::image{
                                                            cow_image, 0.1}} {}

void Cow::act(delta_time dt) {
  t_passed_ += dt;
  if (to_seconds(t_passed_) >= 1) {
    // pick random edge
    int next_index = random_int(0, static_cast<int>(node().num_edges()));
    this->node(node()[next_index].to());
    t_passed_ = from_seconds(0);
  }
}