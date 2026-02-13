#pragma once
#include "Event.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

struct Group;

class Figure {
public:
  sf::Vector2f pos;
  float angle = 0.f;
  float orbitRadius = 0.f;
  sf::Color color = sf::Color::White;

  Group *owner = nullptr;

  virtual ~Figure() = default;
  Figure(sf::Vector2f pos, float orbitRadius);
  virtual void draw(sf::RenderWindow &) {}
  virtual void update(float) {}
  virtual void handleEvent(Event &) {}

  virtual void setAngle(float da) { angle += da; }
  void message(Figure *addr, int code, Figure *info);
};
