#pragma once

#include "Group.h"
#include <cmath>

class SolarBody : public Group {
  float radius;
  float orbitSpeed;
  sf::CircleShape shape;

  float dist(sf::Vector2f a, sf::Vector2f b) {
    return std::hypot(b.x - a.x, b.y - a.y);
  }

public:
  SolarBody(sf::Vector2f pos, float orbitRadius, float r, float speed,
            sf::Color color)
      : Group(pos, orbitRadius) {
    radius = r;
    this->orbitRadius = orbitRadius;
    shape.setOrigin({r, r});
    shape.setRadius(radius);
    shape.setFillColor(color);
  };
  void update(float) override;
  void draw(sf::RenderWindow &w) override;
  // void handleEvent(Event &e) override;
  ~SolarBody() { Group::~Group(); }
};
