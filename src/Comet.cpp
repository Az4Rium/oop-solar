#include "Comet.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

void Comet::update(float dt, int w, int h) {
  pos += velocity * dt;
  if (pos.x < 0 || pos.x > w)
    velocity.x *= -1;
  if (pos.y < 0 || pos.y > h)
    velocity.y *= -1;

  tail.push_front(pos);
  if (tail.size() > 40)
    tail.pop_back();
}

void Comet::draw(sf::RenderWindow &w) {
  int i = 0;
  for (auto &p : tail) {
    float alpha = 255 * (1.f - float(i) / tail.size());

    sf::CircleShape t(radius * (1.f - float(i) / tail.size()));
    t.setOrigin({t.getRadius(), t.getRadius()});
    t.setPosition(p);
    t.setFillColor(sf::Color(200, 200, 255, alpha));

    w.draw(t);
    i++;
  }

  sf::CircleShape head(radius);

  head.setOrigin({radius, radius});
  head.setPosition(pos);
  head.setFillColor(sf::Color::White);

  w.draw(head);
}
