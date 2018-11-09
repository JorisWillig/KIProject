#include "kmint/main.hpp" // voor de main loop
#include "actors/cow.h"
#include "actors/hare.h"
#include "kmint/graphics.hpp" // kleuren en afbeeldingen
#include "kmint/map/map.hpp"
#include "kmint/math/vector2d.hpp" // voor window en app
#include "kmint/play.hpp"          // voor stage
#include "kmint/ui.hpp"            // voor window en app
#include <actors/tester.h>
#include <fstream>
#include <iostream>

using namespace kmint; // alles van libkmint bevindt zich in deze namespace

const map::map_node &find_cow_node(const map::map_graph &graph) {
  for (std::size_t i = 0; i < graph.num_nodes(); ++i) {
    if (graph[i].node_info().kind == 'C') {
      return graph[i];
    }
  }
  throw "could not find starting point";
}

int main() {
  // een app object is nodig om
  ui::app app{};

  //  maak een venster aan
  ui::window window{app.create_window({1024, 768}, "hello")};
  auto mapStream = std::ifstream{"resources/kaart.txt"};
  map::map map{map::read_map(mapStream)};

  // maak een podium aan
  play::stage s{};

  // lees de kaart in
  s.build_actor<play::background>(math::size(1024, 768),
                                  graphics::image{map.background_image()});
  s.build_actor<play::map_actor>(math::vector2d{0.0f, 0.0f}, map.graph());

  // build actors
  auto &cow_node = find_cow_node(map.graph());
  auto &cow = s.build_actor<Cow>(map.graph(), cow_node);
  auto &hare = s.build_actor<Hare>(map.graph());
  hare.set_cow(cow);
  math::vector2d center{512.0, 384.0};
  auto &tester = s.build_actor<Tester>(center);

  // Maak een event_source aan (hieruit kun je alle events halen, zoals
  // toetsaanslagen)
  ui::events::event_source event_source{};

  // main_loop stuurt alle actors aan.
  main_loop(s, window, [&](delta_time dt, loop_controls &ctl) {
    // gebruik dt om te kijken hoeveel tijd versterken is
    // sinds de vorige keer dat deze lambda werd aangeroepen
    // loop controls is een object met eigenschappen die je kunt gebruiken om de
    // main-loop aan te sturen.

    for (ui::events::event &e : event_source) {
      // event heeft een methjode handle_quit die controleert
      // of de gebruiker de applicatie wilt sluiten, en zo ja
      // de meegegeven functie (of lambda) aanroept om met het
      // bijbehorende quit_event
      //
      e.handle_quit([&ctl](ui::events::quit_event qe) { ctl.quit = true; });
      e.handle_key_up([&tester](ui::events::key_event k) {
        switch (k.key) {
        case ui::events::key::up:
          tester.move({0, -5.0f});
          break;
        case ui::events::key::down:
          tester.move({0, 5.0f});
          break;
        case ui::events::key::left:
          tester.move({-5.0f, 0});
          break;
        case ui::events::key::right:
          tester.move({5.0f, 0});
          break;
        default:
          break;
        }
      });
    }
  });
}
