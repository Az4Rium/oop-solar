#pragma once
#include "Event.h"
#include "Group.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdio>
#include <variant>

class Desktop : public Group {
public:
  bool quit = false;
  int figmax;
  float speed = .5f;
  void handleEvent(Event &e) override {
    std::visit(
      Overloaded{
        [&](KeyEvent &k) {
          if (k.key == sf::Keyboard::Key::Escape)
            quit = true;
          if (k.key == sf::Keyboard::Key::A){
            printf("Speed increased\n");
            speed += 0.1f;
          }
          if (k.key == sf::Keyboard::Key::D){
            speed -= 0.1f;
            printf("Speed decreased\n");
          }
        },
        [&](auto &) {},
    },
    e);

    Group::handleEvent(e);
  }
   Desktop(sf::Vector2f pos, float orbitRadius, int figmax);//= default;
  ~Desktop() {
    printf("%lu\n",childern.size());
    for (auto c : childern) {
      delete c;
      printf("Deleted addr:%p\n", c);
    }
  }
};
