#include "Rectangle.h"
#include "Event.h"
#include "Group.h"

void RectangleFigure::update(float angle) {
  if (owner) {
    pos.x = owner->pos.x + orbitRadius * std::cos(this->angle);
    pos.y = owner->pos.y + orbitRadius * std::sin(this->angle);
  }
  shape.setPosition(pos);
  shape.setOutlineColor(color);
  Group::update(angle);
};

void RectangleFigure::draw(sf::RenderWindow &w) {
  w.draw(shape);
  Group::draw(w);
};

void RectangleFigure::handleEvent(Event &e) {
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
                        [&](BroadcastEvent &b) {
                          switch (b.code) {
                          case cmRed:
                            Figure::setColor(255, 0, 0);
                            break;
                          case cmGreen:
                            Figure::setColor(0, 255, 0);
                            break;
                          }
                        },
                        [&](auto &) {}},
             e);
  Group::handleEvent(e);
};
