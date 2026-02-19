#pragma once
#include "Event.h"
#include "Figure.h"
#include "Group.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <cmath>
#include <variant>

class Point : public Figure {
  sf::CircleShape shape;

public:
  float radius;
  Point(sf::Vector2f pos, float orbitRadius, float angle)
      : Figure(pos, orbitRadius) {
    this->pos = pos;
    this->angle = angle;
    this->orbitRadius = orbitRadius;

    radius = 5.f;
    shape.setRadius(radius);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin({radius, radius});
  }
  ~Point() = default;
  virtual void update(float) override;
  void setAngle(float da) override { angle += da * -1.f; }
  void draw(sf::RenderWindow &w) override;
  void handleEvent(Event &e) override;
};
