#pragma once
#include "Event.h"
#include "Figure.h"
#include "Group.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Window.hpp>
#include <cmath>
#include <variant>

class Point : public Figure {
  sf::CircleShape shape;

public:
  float radius;
  Point(float r) : radius(r), shape(r) {
    shape.setOrigin({r, r});
    shape.setRadius(r);
  }
  virtual void update(float) override {
    if (owner) {
      pos.x = owner->pos.x + orbitRadius * std::cos(angle);
      pos.y = owner->pos.y + orbitRadius * std::sin(angle);
    }
    shape.setPosition(pos);
    shape.setFillColor(color);
  }
  void draw(sf::RenderWindow &w) override { w.draw(shape); }
  void handleEvent(Event &e) override {
    std::visit(Overloaded{[&](MouseEvent &m) {
                            auto r = pos - sf::Vector2f(m.x, m.y);
                            if (std::hypot(r.x, r.y) < radius) {
                              message(owner, cmPressPoint, this);
                              e = std::monostate();
                            }
                          },
                          [&](BroadcastEvent &b) {
                            switch (b.code) {
                            case cmRed:
                              color = sf::Color::Red;
                            case cmGreen:
                              color = sf::Color::Green;
                            };
                            e = std::monostate();
                          },
                          [&](auto &) {}},
               e);
  }
};
