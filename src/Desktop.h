#pragma once
#include "Event.h"
#include "Group.h"
#include <SFML/Window/Keyboard.hpp>
#include <variant>

class Desktop : public Group {
public:
  bool quit = false;
  float speed = .5f;
  void handleEvent(Event &e) override {
    std::visit(Overloaded{
                   [&](KeyEvent &k) {
                     if (k.key == sf::Keyboard::Key::Escape)
                       quit = true;
                     if (k.key == sf::Keyboard::Key::A)
                       speed += 0.1f;
                     if (k.key == sf::Keyboard::Key::D)
                       speed -= 0.1f;
                   },
                   [&](auto &) {},
               },
               e);

    Group::handleEvent(e);
  }
  Desktop() = default;
  ~Desktop() {
    for (auto c : childern) {
      delete c;
    }
  }
};
