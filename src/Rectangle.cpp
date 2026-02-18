#include "Rectangle.h"
#include "Circle.h"
#include "Event.h"
#include <SFML/Graphics/CircleShape.hpp>

void RectangleFigure::update(float angle) {
  if (owner) {
    pos.x = owner->pos.x + orbitRadius * std::cos(angle);
    pos.y = owner->pos.y + orbitRadius * std::sin(angle);
  }
  shape.setPosition(pos);
  shape.setFillColor(color);
};

void RectangleFigure::draw(sf::RenderWindow &w) {
  w.draw(shape);
  Group::draw(w);
};

void RectangleFigure::handleEvent(Event &e) {
  Group::handleEvent(e);
  std::visit(Overloaded{[&](MouseEvent &m) {
                          // mouse logic
                          auto d = pos - sf::Vector2f(m.x, m.y);
                          if (d.x > pos.x && d.y > pos.y &&
                              d.x < pos.x /*+ size*/ &&
                              d.y < pos.y /*+ size*/) {
                            message(owner, cmPressRect, this);
                            e = std::monostate{};
                          }
                        },
                        [&](auto &) {}},
             e);
};
