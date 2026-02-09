#pragma once
#include "Group.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>

class Circle : public Group {
  float radius;
  sf::CircleShape shape;

public:
  Circle(float r) : radius(r), shape(r) { shape.setOrigin({r, r}); }
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
};
