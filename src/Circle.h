#pragma once
#include "Event.h"
#include "FreePoint.h"
#include "Group.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <cstdio>

class CircleFigure : public Group {
  float radius;
  sf::CircleShape shape;

  float dist(sf::Vector2f a, sf::Vector2f b) {
    return std::hypot(b.x - a.x, b.y - a.y);
  }

public:
  CircleFigure(sf::Vector2f pos, float orbitRadius, float r, float angle,
               sf::Color color)
      : Group(pos, orbitRadius) {
    radius = r;
    this->angle = angle;
    this->color = color;
    shape.setOrigin({r, r});
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(color);
    shape.setOutlineThickness(5.f);
    shape.setRadius(r);
  };
  void update(float) override;
  float getSize() { return radius; };
  void draw(sf::RenderWindow &w) override;
  void handleEvent(Event &e) override;
  ~CircleFigure() = default;
};
