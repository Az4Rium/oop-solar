#include "Circle.h"
#include "Event.h"
#include "Point.h"
#include <SFML/Graphics/RenderWindow.hpp>

void CircleFigure::update(float angle) {
  if (owner) {
    pos.x = owner->pos.x + orbitRadius * std::cos(this->angle);
    pos.y = owner->pos.y + orbitRadius * std::sin(this->angle);
  }
  shape.setPosition(pos);
  Group::update(angle);
};

void CircleFigure::draw(sf::RenderWindow &w) {
  Group::draw(w);
  w.draw(shape);
};

void CircleFigure::handleEvent(Event &e) {
  std::visit(Overloaded{[&](MouseEvent &m) {
                          // mouse logic
                          auto d = pos - sf::Vector2f(m.x, m.y);
                          if (std::hypot(d.x, d.y) < radius) {
                            message(owner, cmPressRect, this);
                            e = std::monostate{};
                          }
                        },
                        [&](BroadcastEvent &b) {
                          if (b.code == cmCollision) {
                            auto other = static_cast<FreePoint *>(b.info);
                            if (dist(pos, other->pos + other->velocity) +
                                    other->radius <
                                radius) {
                              message(b.info, cmRed, this);
                            }
                          }
                        },
                        [&](auto &) {}},
             e);
  Group::handleEvent(e);
};
