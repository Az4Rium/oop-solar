#pragma once
#include "Point.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>

class FreePoint : public Point {
  sf::CircleShape shape;
  float radius;
  sf::Vector2f velocity;
  int windowWidth, windowHeight; 

public:
  FreePoint(float r, sf::Vector2f initialPos, sf::Vector2f initialVel, int winW,
            int winH)
      : Point(r), velocity(initialVel), windowWidth(winW), windowHeight(winH) {
    pos = initialPos;
    shape.setPosition(pos);
    shape.setFillColor(color);
  }
  void update(float) override {
    if(pos + velocity > sf::Vector2f(windowWidth - radius, windowHeight - radius)||
        pos){

    }
  }
};
