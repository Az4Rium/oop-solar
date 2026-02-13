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
  FreePoint(float r, sf::Vector2f initialPos, sf::Vector2f initialVel, int winW,
            int winH)
      : Point(r), velocity(initialVel), windowWidth(winW), windowHeight(winH) {
    pos = initialPos;
    shape.setPosition(pos);
    shape.setFillColor(color);
    radius = r;
    shape.setRadius(radius);
  }
  void update(float) override {
    if (pos.x + velocity.x > windowWidth - radius || pos.x + velocity.x < 0)
      velocity.x *= -1;
    else
      pos.x += velocity.x;
    if (pos.y + velocity.y > windowHeight - radius || pos.y + velocity.y < 0)
      velocity.y *= -1;
    else
      pos.y += velocity.y;

    shape.setPosition(pos);
    message(nullptr, cmCollision, this);
  }
  void draw(sf::RenderWindow &w) override {
    printf("risu\n");
    w.draw(shape);
  }

  void handleEvent(Event &e) override {
    std::visit(Overloaded{[&](BroadcastEvent &b) {
      if (b.code == cmRed){
        if(b.addr == this){
          velocity.x *= -1;
          velocity.y *= -1;
          pos.x += 5*velocity.x;
          pos.y += 5*velocity.y;
        }
      }
    }, [&](auto &) {}}, e);
  }
  ~FreePoint() = default;
};
