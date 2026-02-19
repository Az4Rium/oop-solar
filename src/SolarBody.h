#pragma once
#include "Group.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class SolarBody : public Group {
  float radius;
  float orbitSpeed;
  sf::CircleShape shape;

public:
  SolarBody(sf::Vector2f pos, float orbitRadius, float r, float speed,
            sf::Color color)
      : Group(pos, orbitRadius) {
    radius = r;
    orbitSpeed = speed;
    shape.setRadius(radius);
    shape.setOrigin({radius, radius});
    shape.setFillColor(color);
  }

  void update(float dt) override;
  void draw(sf::RenderWindow &w) override;
};
