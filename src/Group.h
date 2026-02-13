#pragma once
#include "Event.h"
#include "Figure.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

class Group : public Figure {
public:
  std::vector<Figure *> childern;

  void insert(Figure *f) {
    f->owner = this;
    childern.push_back(f);
  }

  Group(sf::Vector2f pos, float orbitRadius): Figure(pos,orbitRadius){
    childern.clear();
  }
  
  void draw(sf::RenderWindow &w) override{
    for (Figure *f : childern)
      f->draw(w);
  }

  void update(float dt) override {
    for (Figure *f : childern)
      f->update(dt);
  }

  void handleEvent(Event &e) override {
    for (Figure *f : childern)
      f->handleEvent(e);
  }

  void setAngle(float da) override {
    Figure::setAngle(da);
    for (Figure *f : childern)
      f->setAngle(da);
  }
  ~Group() = default;
};
