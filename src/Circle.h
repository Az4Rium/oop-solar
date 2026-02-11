#pragma once
#include "Group.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>

class CircleFigure : public Group {
  float radius;
  sf::CircleShape shape;

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
      [&](KeyEvent &k) {

      },
      [&](BroadcastEvent &b) {

      },
      [&](std::monostate &) {}},
    e);
  }
};
