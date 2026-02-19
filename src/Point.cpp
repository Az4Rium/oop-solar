#include "Point.h"
#include "Event.h"
#include <SFML/Graphics/RenderWindow.hpp>

void Point::update(float angle) {
  if (owner) {
    pos.x = owner->pos.x + orbitRadius * std::cos(this->angle);
    pos.y = owner->pos.y + orbitRadius * std::sin(this->angle);
  }
  shape.setPosition(pos);
};

void Point::draw(sf::RenderWindow &w) { w.draw(shape); }

void Point::handleEvent(Event &e) {
  // std::visit(Overloaded{[&](MouseEvent &m) {
  //                         auto r = pos - sf::Vector2f(m.x, m.y);
  //                         if (std::hypot(r.x, r.y) < radius) {
  //                           message(owner, cmPressPoint, this);
  //                         }
  //                       },
  //                       [&](BroadcastEvent &b) {
  //                         switch (b.code) {
  //                         case cmRed:
  //                           color = sf::Color::Red;
  //                           break;
  //                         case cmGreen:
  //                           color = sf::Color::Green;
  //                           break;
  //                         };
  //                       },
  //                       [&](auto &) {}},
  //            e);
}
