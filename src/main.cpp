#include "Group.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/WindowEnums.hpp>

class Rect : Figure {
private:
}




int main() {
  sf::RenderWindow window(sf::VideoMode({640, 480}), "SFML works!",
                          sf::Style::Close);
  window.setPosition({0, 0});
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  shape.setPosition({320 - 100.0f, 240 - 100.0f});
  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();
    }

    window.clear();
    window.draw(shape);
    window.display();
  }
}
