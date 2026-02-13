#pragma once
#include "Event.h"
#include "FreePoint.h"
#include "Group.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

class CircleFigure : public Group {
  float radius;
  sf::CircleShape shape;

  float dist(sf::Vector2f a, sf::Vector2f b){
    return std::hypot(b.x - a.x,b.y-a.y);
  }
public:
  CircleFigure(float r) : radius(r), shape(r) { shape.setOrigin({r, r}); }
  void update(float) override {
    if (owner) {
      pos.x = owner->pos.x + orbitRadius * std::cos(angle);
      pos.y = owner->pos.y + orbitRadius * std::sin(angle);
    }
    shape.setPosition(pos);
    shape.setFillColor(color);
  }

  void draw(sf::RenderWindow &w) override {
    w.draw(shape);
    sf::CircleShape dot;
    dot.setPosition({pos.x-10.f,pos.y-10.f});
    dot.setFillColor(sf::Color::White);
    dot.setRadius(10.f); 
    Group::draw(w);
    w.draw(dot);
  }

  void handleEvent(Event &e) override {
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
  }
};
