#pragma once
#include "Event.h"
#include "Figure.h"
#include "Point.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <cstdio>
#include <ratio>
#include <variant>

class FreePoint : public Point {
  sf::CircleShape shape;
  int windowWidth, windowHeight;

public:
  float radius;
  sf::Vector2f velocity;
  FreePoint(sf::Vector2f pos, float orbitRadius, float angle,
            sf::Vector2f velocity)
      : Point(pos, orbitRadius, angle) {
    this->orbitRadius = 0;
    this->pos = pos;
    this->velocity = velocity;
    sf::Color(1 + rand() % 255, 1 + rand() % 255, 1 + rand() % 255);
    this->radius = 5.f;
    owner = nullptr;
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setOrigin({radius, radius});
  }
  void update(float) override;
  void draw(sf::RenderWindow &w) override { w.draw(shape); }
  void setWindowSize(sf::Vector2f size) {
    windowHeight = size.y;
    windowWidth = size.x;
  }
  void handleEvent(Event &e) override;
  ~FreePoint() = default;
};
