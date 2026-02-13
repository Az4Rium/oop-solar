#include "Circle.h"
#include "Event.h"
#include <SFML/Graphics/RenderWindow.hpp>

void CircleFigure::update(float angle) {
  if (owner) {
    pos.x = owner->pos.x + orbitRadius * std::cos(angle);
    pos.y = owner->pos.y + orbitRadius * std::sin(angle);
  }
  shape.setPosition(pos);
  shape.setFillColor(color);
};

void CircleFigure::draw(sf::RenderWindow &w) {
  w.draw(shape);
  Group::draw(w);
};

void CircleFigure::handleEvent(Event &e){
  Group::handleEvent(e);
  std::visit(Overloaded{
    [&](MouseEvent &m) {
      // mouse logic
      auto d = pos - sf::Vector2f(m.x,m.y);
      if (std::hypot(d.x, d.y) < radius) {
        message(owner, cmPressRect, this);
        e = std::monostate{};
      }
    },
    [&](BroadcastEvent &b){

      if(b.code == cmCollision){
        auto other = static_cast<FreePoint*>(b.info);
        if (dist(pos,other->pos + other->velocity)+other->radius<radius){
          message(b.info,cmRed,this);
        }
      }
    },
    [&](auto &){}},
  e);
};

