#pragma once
#include "Event.h"
#include "Group.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>
#include <type_traits>
#include <variant>
class RectangleFigure : public Group {
  float size;
  sf::RectangleShape shape;

public:
  RectangleFigure(float s) : size(s), shape({s, s}) {
    shape.setOrigin({s, s});
  };

  void update(float) override {
    if (owner) {
      pos.x = owner->pos.x + orbitRadius * std::cos(angle);
      pos.y = owner->pos.y + orbitRadius * std::sin(angle);
    }
    shape.setPosition(pos);
    shape.setFillColor(color);
  }

  void draw(sf::RenderWindow &w) override {
    w.draw(shape);
    Group::draw(w);
  }

  void handleEvent(Event &e) override {
    std::visit(
        [&](auto &&ev) {
          using T = std::decay_t<decltype(ev)>;

          if constexpr (std::is_same_v<T, MouseEvent>) {
            auto d = pos - sf::Vector2f(ev.x, ev.y);
            if (std::hypot(d.x, d.y) < size) {
              message(owner, 102, this);
              e = std::monostate{};
            }
          }
        },
        e);
  }
};
