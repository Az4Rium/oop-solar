#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdlib>
#include <deque>

class Comet {
  sf::Vector2f pos;
  sf::Vector2f velocity;

  float radius = 4.f;
  std::deque<sf::Vector2f> tail;

public:
  Comet(int w, int h) {
    pos = {float(rand() % w), float(rand() % h)};
    velocity = {float(rand() % 200 - 100), float(rand() % 200 - 100)};
  }

  void update(float dt, int w, int h);
  void draw(sf::RenderWindow &w);
};
