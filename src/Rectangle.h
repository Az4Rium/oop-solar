#pragma once
#include "Event.h"
#include "Group.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <cmath>
#include <type_traits>
#include <variant>
class RectangleFigure : public Group {
  float size;
  sf::RectangleShape shape;

public:
  RectangleFigure(float s) : size(s), shape({s, s}) {
    shape.setOrigin({s/2, s/2});
  };

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
        if (d.x > pos.x && d.y > pos.y && d.x < pos.x + size && d.y < pos.y + size) {
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
