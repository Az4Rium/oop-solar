#include "Point.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>

class FreePoint : public Point {
  sf::CircleShape shape;
  float radius;
  sf::Vector2f velocity;         // dx, dy
  int windowWidth, windowHeight; // for boundary check

public:
  FreePoint(float r, sf::Vector2f initialPos, sf::Vector2f initialVel, int winW,
            int winH)
      : Point(r), velocity(initialVel), windowWidth(winW), windowHeight(winH) {
    pos = initialPos;
    shape.setPosition(pos);
    shape.setFillColor(color);
  }

  void update(float dt) override {
    // Move
    pos += velocity * dt;

    // Bounce on X
    if (pos.x - radius < 0 || pos.x + radius > windowWidth)
      velocity.x = -velocity.x;

    // Bounce on Y
    if (pos.y - radius < 0 || pos.y + radius > windowHeight)
      velocity.y = -velocity.y;

    // Random color change
    shape.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));

    // Update base Point stuff
    Point::update(dt);

    // Broadcast collision (you can implement message system)
    // message(nullptr, cmBroadCast, cmCollision, this);
  }

  void handleEvent(Event &e) override {
    std::visit(Overloaded{
                   [&](BroadcastEvent &b) {
                     switch (b.code) {
                     case cmRed:
                       velocity = -velocity;
                       pos += 5.0f * velocity;
                       color = sf::Color::Red;
                       break;
                     case cmGreen:
                       velocity = -velocity;
                       pos += 5.0f * velocity;
                       color = sf::Color::Green;
                       break;
                     }
                   },
                   [&](auto &) { Point::handleEvent(e); } // fallback to base
               },
               e);
  }
};
