#pragma once
#include "Event.h"
#include "Group.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <type_traits>
#include <variant>
class RectangleFigure : public Group {
  float size;
  sf::RectangleShape shape;

public:
  ~RectangleFigure() = default;
  RectangleFigure(sf::Vector2f pos, float orbitRadius, float size,float angle) : Group(pos, orbitRadius){
    this->size = size;
    shape.setSize({size,size});
    shape.setOrigin({size/2,size/2});
  };
  void update(float) override;

  void draw(sf::RenderWindow &w) override;
  void handleEvent(Event &e) override;
};
